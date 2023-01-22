#include "ServerSocket.hpp"

#include "Engine/Engine.hpp"

namespace mtEngine
{
  ServerSocket *ServerSocket::Instance = nullptr;

  ServerSocket::ServerSocket()
      : sock(0)
      , fd(0)
      , running(true)
  {
    Instance = this;
    PLOGI << "Server starting...";
  }

  ServerSocket::~ServerSocket()
  {
    PLOGI << "Server shutdown";
  }

  auto ServerSocket::Init() -> std::unique_ptr<ServerSocket>
  {
    auto socket = std::make_unique<ServerSocket>();
    socket->create();

    return socket;
  }

  auto ServerSocket::create() -> void
  {
    int len = 0;

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == fd)
    {
      PLOGE << "Error on socket() call";
      return;
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCKET_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(fd, (struct sockaddr *)&local, len) != 0)
    {
      PLOGE << "Error on bind() call";
      return;
    }

    if (listen(fd, nIncomingConnections) != 0)
    {
      PLOGE << "Error on listen call";
    }
  }

  auto ServerSocket::run() -> void
  {
    std::thread task_;
    while (running)
    {
      unsigned int sock_len = 0;
      PLOGI << "Waiting for connection...";
      if ((sock = accept(fd, (struct sockaddr *)&remote, &sock_len)) == -1)
      {
        PLOGI << "Error on accept() call";
        return;
      }
      clients.push_back(sock);

      PLOGI << "Server connected";

      task_ = std::thread([this]() { this->handler(sock, std::ref(running)); });
      task_.detach();
    }
    close(sock);
  }

  auto ServerSocket::shutdown() -> void
  {
    {
      // some sockets thread may stay worked after request
      // reconnect to server, send stop command and close at once: forcing shutdown
      static const unsigned int s_recv_len = 200;
      static const unsigned int s_send_len = 100;

      int _sock = 0;
      int data_len = 0;
      struct sockaddr_un remote;
      char recv_msg[s_recv_len];
      char send_msg[s_send_len];

      memset(recv_msg, 0, s_recv_len * sizeof(char));
      memset(send_msg, 0, s_send_len * sizeof(char));

      if ((_sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
      {
        return;
      }

      remote.sun_family = AF_UNIX;
      strcpy(remote.sun_path, SOCKET_PATH);
      data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

      if (connect(_sock, (struct sockaddr *)&remote, data_len) == -1)
      {
        return;
      }
      send(_sock, STOP_COMMAND, strlen(STOP_COMMAND) * sizeof(char), 0);
      close(_sock);
    }

    running = false;
    Engine::Get()->RequestClose();
    PLOGI << "server request shutdown";
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  auto ServerSocket::handler(int socket, std::atomic_bool &running) -> void
  {
    char client_message[256];
    memset(&client_message, 0, 256);
    size_t message_size = 0;

    PLOGI << "Client Connected";

    while ((message_size = recv(socket, client_message, sizeof(client_message) - 1, 0)) > 0)
    {
      client_message[message_size] = '\0';
      PLOGI << "Client message: " << client_message;

      if (strstr(client_message, "quit") != 0)
      {
        PLOGD << "Client requested quit";
        shutdown();
        send(socket, "Server shutdown", strlen("Server shutdown") * sizeof(char), 0);
        break;
      }

      if (write(socket, client_message, message_size) == -1)
      {
        PLOGI << "Client message sendig failed";
        break;
      }
    }

    PLOGI << "Client Thread finished";
  }

} // namespace mtEngine
