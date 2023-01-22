#pragma once

#include <atomic>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <vector>

#include "Utils/NonCopyable.hpp"
#include "third_party/plog/Log.h"

namespace mtEngine
{
  class ServerSocket : public NonCopyable
  {
  public:
    constexpr static const char *SOCKET_PATH = "/tmp/mtEngine.sock";
    constexpr static const char *STOP_COMMAND = "stop";
    constexpr static const unsigned int nIncomingConnections = 5;

    ServerSocket();
    ~ServerSocket();

    auto static Init() -> std::unique_ptr<ServerSocket>;

    static ServerSocket *Get() { return Instance; }

    auto create() -> void;

    auto run() -> void;

    auto shutdown() -> void;

  private:
    auto handler(int socket, std::atomic_bool &running) -> void;

  private:
    static ServerSocket *Instance;
    std::atomic_bool running;

    struct sockaddr_un local, remote;
    int sock;
    int fd;
    std::vector<int> clients;
  };
} // namespace mtEngine
