#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <vector>

#include "Utils/Delegate.hpp"
#include "Utils/NonCopyable.hpp"
#include "third_party/plog/Log.h"

namespace mtEngine
{
  class ServerSocket : public NonCopyable
  {
  private:
    struct SocketFD;
    SocketFD *sockFd;

  public:
    constexpr static const char *SOCKET_PATH = "/tmp/mtEngine.sock";
    constexpr static const char *USER_AGENT = "mtEngine";
    constexpr static const char *STOP_COMMAND = "shutdown";
    constexpr static const unsigned int nIncomingConnections = 5;
    constexpr static const int SOCKET_ERROR = -1;

    ServerSocket();

    ~ServerSocket();

    auto static Init() -> std::unique_ptr<ServerSocket>;

    auto IsRun() -> bool const { return m_ServerRun; }

    auto static Get() -> ServerSocket *const { return Instance; }

    // ---------------------------------------------------------------------------
    // Server emit message to all connected clients
    auto emit(const std::string &msg) -> void;

    // ---------------------------------------------------------------------------
    // Get last message sending by any client
    auto recieve() -> std::string const { return m_lastMessage; }

    // ---------------------------------------------------------------------------
    // Waiting all clients threads is finished
    auto waitAllClientsDisconnected() -> void;

    // ---------------------------------------------------------------------------
    // Listen for accepting connection
    auto startListen() -> void;

    // ---------------------------------------------------------------------------
    // Disconnect all clients.
    auto disconnectAll() -> void;

    // ---------------------------------------------------------------------------
    // Force disconnect clients and shutdown server.
    // If <wait=true> server waiting all clients then shutdown.
    // If <wait=false> server stopped immediately,
    // but clients will be running in background on separated threads.
    // In this case jobs in threads are not controllable. They are stopped when are will be done.
    auto shutdown(const bool &wait = true) -> void;

    // ---------------------------------------------------------------------------
    // Event server on recieved message.
    // Event work only if filter equals message
    auto OnRecieve() -> Delegate<void(std::string)> &;

  private:
    // ---------------------------------------------------------------------------
    // Call all sockets routine in on function
    auto socketInit() -> bool;

    // ---------------------------------------------------------------------------
    // Create and open socket file description
    auto socketOpen(const char *path) -> bool;

    // ---------------------------------------------------------------------------
    // Bind a name to a opened socket
    auto socketBind() -> bool;

    // ---------------------------------------------------------------------------
    // Start listen for connection
    auto socketListen(int max) -> bool;

    // ---------------------------------------------------------------------------
    // Accept a connection on a socket
    // This is run in a separate thread for each socket.
    auto socketAccept() -> int;

    // ---------------------------------------------------------------------------
    // Accept a non blocking connection on a socket
    // This is run in a separate thread for each socket.
    auto socketAcceptNonBlocking() -> int;

    // ---------------------------------------------------------------------------
    // Disconnect specific client.
    auto disconnectClient(const int socket) -> void;

    // ---------------------------------------------------------------------------
    // Process a connection.
    // This is run in a separate thread for each socket.
    auto connectionHandler(const int client) -> void;

    // ---------------------------------------------------------------------------
    // Get socket descriptor.
    auto getDescriptor() -> SocketFD *;

  private:
    struct SocketFD
    {
      int fd = 0;
      int fd_len = 0;
      struct sockaddr_un local;
      struct sockaddr_un remote;
      const char *unix_address;
      unsigned int socket_len = 0;
    };

    // server run flag
    std::atomic_bool m_ServerRun;

    // last message sended by any client
    std::string m_lastMessage;

    // connected clients storage
    std::vector<int> m_clients;

    // whait clients in detached threads before server shutdown
    bool m_whaitClientsBeforeQuit;

    static ServerSocket *Instance;

    u_int16_t totalSend;

    Delegate<void(std::string)> onRecieve;
  };
} // namespace mtEngine
