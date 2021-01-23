#ifndef RTC_BASE_ASYNC_UDP_SOCKET_H_
#define RTC_BASE_ASYNC_UDP_SOCKET_H_

#include <stddef.h>

#include <memory>

#include "async_packet_socket.h"
#include "async_socket.h"
#include "socket.h"
#include "socket_address.h"
#include "socket_factory.h"

using namespace MSF;

namespace MSF {

// Provides the ability to receive packets asynchronously.  Sends are not
// buffered since it is acceptable to drop packets under high load.
class AsyncUDPSocket : public AsyncPacketSocket {
 public:
  // Binds |socket| and creates AsyncUDPSocket for it. Takes ownership
  // of |socket|. Returns null if bind() fails (|socket| is destroyed
  // in that case).
  static AsyncUDPSocket* Create(AsyncSocket* socket,
                                const SocketAddress& bind_address);
  // Creates a new socket for sending asynchronous UDP packets using an
  // asynchronous socket from the given factory.
  static AsyncUDPSocket* Create(SocketFactory* factory,
                                const SocketAddress& bind_address);
  explicit AsyncUDPSocket(AsyncSocket* socket);
  ~AsyncUDPSocket() override;

  SocketAddress GetLocalAddress() const override;
  SocketAddress GetRemoteAddress() const override;
  int Send(const void* pv, size_t cb, const PacketOptions& options) override;
  int SendTo(const void* pv, size_t cb, const SocketAddress& addr,
             const PacketOptions& options) override;
  int Close() override;

  State GetState() const override;
  int GetOption(Socket::Option opt, int* value) override;
  int SetOption(Socket::Option opt, int value) override;
  int GetError() const override;
  void SetError(int error) override;

 private:
  // Called when the underlying socket is ready to be read from.
  void OnReadEvent(AsyncSocket* socket);
  // Called when the underlying socket is ready to send.
  void OnWriteEvent(AsyncSocket* socket);

  std::unique_ptr<AsyncSocket> socket_;
  char* buf_;
  size_t size_;
};

}  // namespace MSF

#endif  // RTC_BASE_ASYNC_UDP_SOCKET_H_