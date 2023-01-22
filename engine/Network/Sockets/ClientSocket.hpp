#pragma once

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "Network/Sockets/ServerSocket.hpp"
#include "third_party/plog/Log.h"

namespace mtEngine
{
  class ClientSocket
  {
  public:
    constexpr static const unsigned int s_recv_len = 200;
    constexpr static const unsigned int s_send_len = 100;

    ClientSocket();
    ~ClientSocket();

    static auto Init() -> std::unique_ptr<ClientSocket>;

    auto makeConnection() -> void;

    auto requestShutdown() -> void;

    auto closeConnection() -> void { close(sock); }

  private:
    struct sockaddr_un remote;
    int sock;
    int data_len;
    char recv_msg[s_recv_len];
    char send_msg[s_send_len];
  };
} // namespace mtEngine
