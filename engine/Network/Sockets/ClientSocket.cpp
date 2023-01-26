#include "ClientSocket.hpp"

namespace mtEngine
{
  ClientSocket *ClientSocket::m_instance = nullptr;

  ClientSocket::ClientSocket()
      : sock(-1)
      , data_len(0)
  {
    m_instance = this;
    PLOGI << "Internal client starting...";
  };

  ClientSocket::~ClientSocket()
  {
    closeConnection();
    m_instance = nullptr;
    PLOGI << "Internal client terminated...";
  };

  auto ClientSocket::Init() -> std::unique_ptr<ClientSocket>
  {
    auto socket = std::make_unique<ClientSocket>();
    socket->makeConnection();
    return socket;
  }

  auto ClientSocket::CloseConnection() -> void
  {
    ClientSocket::Get()->closeConnection();
  }

  auto ClientSocket::makeConnection() -> void
  {
    memset(recv_msg, 0, s_recv_len * sizeof(char));
    memset(send_msg, 0, s_send_len * sizeof(char));
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
      PLOGE << "Internal client: Error on socket() call";
      return;
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, ServerSocket::SOCKET_PATH);
    data_len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    PLOGI << "Internal client connecting...";
    if (connect(sock, (struct sockaddr *)&remote, data_len) == -1)
    {
      PLOGE << "Internal client error connect";
      return;
    }

    PLOGI << "Internal client connected";
  }

  auto ClientSocket::requestShutdown() -> void
  {
    PLOGI << "Internal client send shutdown command";
    send(sock, ServerSocket::STOP_COMMAND, strlen(ServerSocket::STOP_COMMAND), 0);
  }
} // namespace mtEngine
