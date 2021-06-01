#include "async_tcp_socket.h"

#include <stdint.h>
#include <string.h>

#include <algorithm>
#include <memory>
#include <base/logging.h>

#include "array_view.h"
#include "byte_order.h"
#include "sent_packet.h"
#include "sigslot.h"
#include "time_utils.h"  // for TimeMillis

#if defined(__linux__)
#include <errno.h>
#endif  // WEBRTC_POSIX

namespace MSF {

static const size_t kMaxPacketSize = 64 * 1024;

typedef uint16_t PacketLength;
static const size_t kPacketLenSize = sizeof(PacketLength);

static const size_t kBufSize = kMaxPacketSize + kPacketLenSize;

// The input buffer will be resized so that at least kMinimumRecvSize bytes can
// be received (but it will not grow above the maximum size passed to the
// constructor).
static const size_t kMinimumRecvSize = 128;

static const int kListenBacklog = 5;

// Binds and connects |socket|
AsyncSocket* AsyncTCPSocketBase::ConnectSocket(
    AsyncSocket* socket, const SocketAddress& bind_address,
    const SocketAddress& remote_address) {
  std::unique_ptr<AsyncSocket> owned_socket(socket);
  if (socket->Bind(bind_address) < 0) {
    LOG(ERROR) << "Bind() failed with error " << socket->GetError();
    return nullptr;
  }
  if (socket->Connect(remote_address) < 0) {
    LOG(ERROR) << "Connect() failed with error " << socket->GetError();
    return nullptr;
  }
  return owned_socket.release();
}

AsyncTCPSocketBase::AsyncTCPSocketBase(AsyncSocket* socket, bool listen,
                                       size_t max_packet_size)
    : socket_(socket),
      listen_(listen),
      max_insize_(max_packet_size),
      max_outsize_(max_packet_size) {
  if (!listen_) {
    // Listening sockets don't send/receive data, so they don't need buffers.
    inbuf_.EnsureCapacity(kMinimumRecvSize);
  }

  assert(socket_.get() != nullptr);
  socket_->SignalConnectEvent.connect(this,
                                      &AsyncTCPSocketBase::OnConnectEvent);
  socket_->SignalReadEvent.connect(this, &AsyncTCPSocketBase::OnReadEvent);
  socket_->SignalWriteEvent.connect(this, &AsyncTCPSocketBase::OnWriteEvent);
  socket_->SignalCloseEvent.connect(this, &AsyncTCPSocketBase::OnCloseEvent);

  if (listen_) {
    if (socket_->Listen(kListenBacklog) < 0) {
      LOG(ERROR) << "Listen() failed with error " << socket_->GetError();
    }
  }
}

AsyncTCPSocketBase::~AsyncTCPSocketBase() {}

SocketAddress AsyncTCPSocketBase::GetLocalAddress() const {
  return socket_->GetLocalAddress();
}

SocketAddress AsyncTCPSocketBase::GetRemoteAddress() const {
  return socket_->GetRemoteAddress();
}

int AsyncTCPSocketBase::Close() { return socket_->Close(); }

AsyncTCPSocket::State AsyncTCPSocketBase::GetState() const {
  switch (socket_->GetState()) {
    case Socket::CS_CLOSED:
      return STATE_CLOSED;
    case Socket::CS_CONNECTING:
      if (listen_) {
        return STATE_BOUND;
      } else {
        return STATE_CONNECTING;
      }
    case Socket::CS_CONNECTED:
      return STATE_CONNECTED;
    default:
      return STATE_CLOSED;
  }
}

int AsyncTCPSocketBase::GetOption(Socket::Option opt, int* value) {
  return socket_->GetOption(opt, value);
}

int AsyncTCPSocketBase::SetOption(Socket::Option opt, int value) {
  return socket_->SetOption(opt, value);
}

int AsyncTCPSocketBase::GetError() const { return socket_->GetError(); }

void AsyncTCPSocketBase::SetError(int error) {
  return socket_->SetError(error);
}

int AsyncTCPSocketBase::SendTo(const void* pv, size_t cb,
                               const SocketAddress& addr,
                               const PacketOptions& options) {
  const SocketAddress& remote_address = GetRemoteAddress();
  if (addr == remote_address) return Send(pv, cb, options);
  // Remote address may be empty if there is a sudden network change.
  assert(remote_address.IsNil());
  socket_->SetError(ENOTCONN);
  return -1;
}

int AsyncTCPSocketBase::FlushOutBuffer() {
  assert(!listen_);
  assert(outbuf_.size() > 0);
  ArrayView<uint8_t> view = outbuf_;
  int res;
  while (view.size() > 0) {
    res = socket_->Send(view.data(), view.size());
    if (res <= 0) {
      break;
    }
    if (static_cast<size_t>(res) > view.size()) {
      res = -1;
      break;
    }
    view = view.subview(res);
  }
  if (res > 0) {
    // The output buffer may have been written out over multiple partial Send(),
    // so reconstruct the total written length.
    assert(view.size() == 0);
    res = outbuf_.size();
    outbuf_.Clear();
  } else {
    // There was an error when calling Send(), so there will still be data left
    // to send at a later point.
    assert(view.size() > 0);
    // In the special case of EWOULDBLOCK, signal that we had a partial write.
    if (socket_->GetError() == EWOULDBLOCK) {
      res = outbuf_.size() - view.size();
    }
    if (view.size() < outbuf_.size()) {
      ::memmove(outbuf_.data(), view.data(), view.size());
      outbuf_.SetSize(view.size());
    }
  }
  return res;
}

void AsyncTCPSocketBase::AppendToOutBuffer(const void* pv, size_t cb) {
  assert(outbuf_.size() + cb <= max_outsize_);
  assert(!listen_);
  outbuf_.AppendData(static_cast<const uint8_t*>(pv), cb);
}

void AsyncTCPSocketBase::OnConnectEvent(AsyncSocket* socket) {
  SignalConnect(this);
}

void AsyncTCPSocketBase::OnReadEvent(AsyncSocket* socket) {
  assert(socket_.get() == socket);

  if (listen_) {
    SocketAddress address;
    AsyncSocket* new_socket = socket->Accept(&address);
    if (!new_socket) {
      // TODO(stefan): Do something better like forwarding the error
      // to the user.
      LOG(ERROR) << "TCP accept failed with error " << socket_->GetError();
      return;
    }

    HandleIncomingConnection(new_socket);

    // Prime a read event in case data is waiting.
    new_socket->SignalReadEvent(new_socket);
  } else {
    size_t total_recv = 0;
    while (true) {
      size_t free_size = inbuf_.capacity() - inbuf_.size();
      if (free_size < kMinimumRecvSize && inbuf_.capacity() < max_insize_) {
        inbuf_.EnsureCapacity(std::min(max_insize_, inbuf_.capacity() * 2));
        free_size = inbuf_.capacity() - inbuf_.size();
      }

      int len =
          socket_->Recv(inbuf_.data() + inbuf_.size(), free_size, nullptr);
      if (len < 0) {
        // TODO(stefan): Do something better like forwarding the error to the
        // user.
        if (!socket_->IsBlocking()) {
          LOG(ERROR) << "Recv() returned error: " << socket_->GetError();
        }
        break;
      }

      total_recv += len;
      inbuf_.SetSize(inbuf_.size() + len);
      if (!len || static_cast<size_t>(len) < free_size) {
        break;
      }
    }

    if (!total_recv) {
      return;
    }

    size_t size = inbuf_.size();
    ProcessInput(inbuf_.data<char>(), &size);

    if (size > inbuf_.size()) {
      LOG(ERROR) << "input buffer overflow";
      inbuf_.Clear();
    } else {
      inbuf_.SetSize(size);
    }
  }
}

void AsyncTCPSocketBase::OnWriteEvent(AsyncSocket* socket) {
  assert(socket_.get() == socket);

  if (outbuf_.size() > 0) {
    FlushOutBuffer();
  }

  if (outbuf_.size() == 0) {
    SignalReadyToSend(this);
  }
}

void AsyncTCPSocketBase::OnCloseEvent(AsyncSocket* socket, int error) {
  SignalClose(this, error);
}

// AsyncTCPSocket
// Binds and connects |socket| and creates AsyncTCPSocket for
// it. Takes ownership of |socket|. Returns null if bind() or
// connect() fail (|socket| is destroyed in that case).
AsyncTCPSocket* AsyncTCPSocket::Create(AsyncSocket* socket,
                                       const SocketAddress& bind_address,
                                       const SocketAddress& remote_address) {
  return new AsyncTCPSocket(
      AsyncTCPSocketBase::ConnectSocket(socket, bind_address, remote_address),
      false);
}

AsyncTCPSocket::AsyncTCPSocket(AsyncSocket* socket, bool listen)
    : AsyncTCPSocketBase(socket, listen, kBufSize) {}

int AsyncTCPSocket::Send(const void* pv, size_t cb,
                         const PacketOptions& options) {
  if (cb > kBufSize) {
    SetError(EMSGSIZE);
    return -1;
  }

  // If we are blocking on send, then silently drop this packet
  if (!IsOutBufferEmpty()) return static_cast<int>(cb);

  PacketLength pkt_len = HostToNetwork16(static_cast<PacketLength>(cb));
  AppendToOutBuffer(&pkt_len, kPacketLenSize);
  AppendToOutBuffer(pv, cb);

  int res = FlushOutBuffer();
  if (res <= 0) {
    // drop packet if we made no progress
    ClearOutBuffer();
    return res;
  }

  SentPacket sent_packet(options.packet_id, TimeMillis(),
                         options.info_signaled_after_sent);
  CopySocketInformationToPacketInfo(cb, *this, false, &sent_packet.info);
  SignalSentPacket(this, sent_packet);

  // We claim to have sent the whole thing, even if we only sent partial
  return static_cast<int>(cb);
}

void AsyncTCPSocket::ProcessInput(char* data, size_t* len) {
  SocketAddress remote_addr(GetRemoteAddress());

  while (true) {
    if (*len < kPacketLenSize) return;

    PacketLength pkt_len = GetBE16(data);
    if (*len < kPacketLenSize + pkt_len) return;

    SignalReadPacket(this, data + kPacketLenSize, pkt_len, remote_addr,
                     TimeMicros());

    *len -= kPacketLenSize + pkt_len;
    if (*len > 0) {
      memmove(data, data + kPacketLenSize + pkt_len, *len);
    }
  }
}

void AsyncTCPSocket::HandleIncomingConnection(AsyncSocket* socket) {
  SignalNewConnection(this, new AsyncTCPSocket(socket, false));
}

}  // namespace rtc
