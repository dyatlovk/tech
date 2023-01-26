#include "ServerSocket.hpp"

#include <algorithm>
#include <thread>

#include "Engine/Engine.hpp"

namespace mtEngine
{
  ServerSocket *ServerSocket::Instance = nullptr;

  // ---------------------------------------------------------------------------
  ServerSocket::ServerSocket()
      : m_ServerRun(true)
      , m_lastMessage("")
      , m_clients({})
      , m_whaitClientsBeforeQuit(true)
      , sockFd(nullptr)
  {
    sockFd = new SocketFD;
    Instance = this;
  }

  // ---------------------------------------------------------------------------
  ServerSocket::~ServerSocket()
  {
    m_clients.clear();
    m_ServerRun = false;
    m_lastMessage = "";
    delete sockFd;
    Instance = nullptr;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::Init() -> std::unique_ptr<ServerSocket>
  {
    auto s = std::make_unique<ServerSocket>();
    if (!s->socketInit())
    {
      PLOGE << "error on open socket";

      return nullptr;
    }

    std::thread trd(&ServerSocket::startListen, s.get());
    trd.detach();

    return s;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::emit(const std::string &msg) -> void
  {
    for (const auto &c : m_clients)
    {
      send(c, msg.c_str(), strlen(msg.c_str()) * sizeof(char), 0);
    }
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::waitAllClientsDisconnected() -> void
  {
    PLOGI << "waiting connected clients: " << m_clients.size();
    while (m_clients.size() > 0)
    {
      continue;
    }
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::startListen() -> void
  {
    PLOGD << "Server listen ready...";
    while (m_ServerRun)
    {
      int sock = socketAccept();
      if (sock > 0)
      {
        std::thread trd(&ServerSocket::connectionHandler, this, std::ref(sock));
        trd.detach();
      }
      else
      {
        PLOGE << "error on accept socket";
      }
    }

    PLOGD << "Server stop listen";
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::disconnectAll() -> void
  {
    for (const auto &c : m_clients)
    {
      close(c);
    }
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::shutdown(const bool &wait) -> void
  {
    emit(ServerSocket::STOP_COMMAND);
    if (wait)
    {
      waitAllClientsDisconnected();
    }
    disconnectAll();
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketInit() -> bool
  {
    if (!socketOpen(SOCKET_PATH))
    {
      PLOGF << "error open socket";
      return false;
    }

    if (!socketBind())
    {
      PLOGF << "error bind socket";
      return false;
    }

    if (!socketListen(nIncomingConnections))
    {
      PLOGF << "error listen socket";
      return false;
    }

    return true;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketOpen(const char *path) -> bool
  {
    sockFd->fd = socket(AF_UNIX, SOCK_STREAM, 0);
    sockFd->unix_address = path;

    if (-1 == sockFd->fd)
    {
      PLOGF << "Error on socket() call";
      return false;
    }

    sockFd->local.sun_family = AF_UNIX;
    strcpy(sockFd->local.sun_path, sockFd->unix_address);
    unlink(sockFd->local.sun_path);
    sockFd->fd_len = strlen(sockFd->local.sun_path) + sizeof(sockFd->local.sun_family);

    return true;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketBind() -> bool
  {
    if (bind(sockFd->fd, (struct sockaddr *)&sockFd->local, sockFd->fd_len) != 0)
    {
      PLOGF << "Error on binding socket";
      return false;
    }

    return true;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketListen(int max) -> bool
  {
    if (listen(sockFd->fd, max) != 0)
    {
      PLOGF << "Error on listen call";
      return false;
    }

    return true;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketAccept() -> int
  {
    const auto descriptor = getDescriptor();
    int socket = -1;
    unsigned int sock_len = 0;
    if ((socket = accept(descriptor->fd, (struct sockaddr *)&descriptor->remote, &sock_len)) == SOCKET_ERROR)
    {
      PLOGF << "error accept socket";
      return SOCKET_ERROR;
    }

    m_clients.push_back(socket);

    return socket;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::socketAcceptNonBlocking() -> int
  {
    const auto descriptor = getDescriptor();
    fd_set readfds;
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    int activity;
    FD_ZERO(&readfds);
    FD_SET(descriptor->fd, &readfds);
    getsockopt(descriptor->fd, SOL_SOCKET, SO_RCVTIMEO, NULL, NULL);

    activity = select(descriptor->fd + 1, &readfds, NULL, NULL, &timeout);

    if ((activity < 0) && (errno != EINTR))
    {
      PLOGE << "select error";
    }

    if (activity > 0)
    {
      if (FD_ISSET(descriptor->fd, &readfds))
      {
        int sock = socketAccept();
        if (sock == SOCKET_ERROR)
        {
          return -1;
        }
        return sock;
      }
    }

    return -1;
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::disconnectClient(const int client) -> void
  {
    m_clients.erase(std::find(m_clients.begin(), m_clients.end(), client));
    close(client);
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::connectionHandler(const int client) -> void
  {
    PLOGI << "Client connected: [" << client << "]";

    char client_message[1024];
    memset(&client_message, 0, 1024);

    while (m_ServerRun)
    {
      m_lastMessage = "";
      size_t message_size = 0;

      message_size = recv(client, client_message, sizeof(client_message) - 1, 0);
      client_message[message_size] = '\0';
      if (message_size == -1)
      {
        if (errno == EWOULDBLOCK || errno == EAGAIN)
        {
          PLOGE << std::strerror(errno);
          continue;
        }
      }

      if (message_size == 0)
      {
        break;
      }

      if (strstr(client_message, STOP_COMMAND) != 0)
      {
        emit("shutdown");
        m_ServerRun = false;
        Engine::Get()->RequestClose();
        break;
      }

      PLOGI << "Client [ " << client << " ]"
            << " message:" << client_message;
      m_lastMessage = client_message;

      if (write(client, client_message, message_size) == -1)
      {
        PLOGE << "Client: [" << client << "] message sending failed";
        m_ServerRun = false;
        break;
      }
    }

    disconnectClient(client);

    PLOGI << "Client [" << client << "] disconnect";
  }

  // ---------------------------------------------------------------------------
  auto ServerSocket::getDescriptor() -> SocketFD *
  {
    return sockFd;
  }
} // namespace mtEngine
