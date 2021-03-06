/**************************************************************************
 *
 * Copyright (c) 2017-2021, luotang.me <wypx520@gmail.com>, China.
 * All rights reserved.
 *
 * Distributed under the terms of the GNU General Public License v2.
 *
 * This software is provided 'as is' with no explicit or implied warranties
 * in respect of its properties, including, but not limited to, correctness
 * and/or fitness for purpose.
 *
 **************************************************************************/
#include "connector.h"
#include "sock_utils.h"
#include <base/logging.h>
#include "tcp_connection.h"

namespace MSF {

Connector::Connector(EventLoop *loop, const InetAddress &peer) {}

Connector::~Connector() {}

bool Connector::Connect() {
  int fd = ConnectTcpServer("127.0.01", 8888, SOCK_STREAM);
  if (fd < 0) {
    return false;
  }
  conn_.reset(new TCPConnection(loop_, fd));

  // fd_ = ConnectUnixServer(srvPath.c_str(), cliPath.c_str());
  // if (fd_ < 0) {
  //   return false;
  // }
  return true;
}

}  // namespace MSF