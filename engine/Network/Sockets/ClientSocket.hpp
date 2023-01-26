#pragma once

#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "Network/Sockets/ServerSocket.hpp"
#include "Utils/NonCopyable.hpp"
#include "third_party/plog/Log.h"

namespace mtEngine
{
  class ClientSocket : public NonCopyable
  {
  public:
    constexpr static const unsigned int s_recv_len = 200;
    constexpr static const unsigned int s_send_len = 100;

    ClientSocket();
    ~ClientSocket();

    auto static Init() -> std::unique_ptr<ClientSocket>;

    auto static CloseConnection() -> void;

    auto static Get() -> ClientSocket *const { return m_instance; };

    auto requestShutdown() -> void;

  private:
    auto closeConnection() -> void { close(sock); }

    auto makeConnection() -> void;

  private:
    struct sockaddr_un remote;
    int sock;
    int data_len;
    char recv_msg[s_recv_len];
    char send_msg[s_send_len];

    static ClientSocket *m_instance;
  };
} // namespace mtEngine
