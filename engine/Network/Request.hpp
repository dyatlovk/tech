#pragma once

#include "Config.hpp"
#include "Network/Sockets/ServerSocket.hpp"
#include "Utils/String.hpp"

namespace mtEngine::Network
{
  // ---------------------------------------------------------------------------
  struct Request;

  namespace ContentType
  {
    enum Types
    {
      JSON,
      PLAIN,
      BINARY
    };

    // ---------------------------------------------------------------------------
    // Convert type to string
    inline auto typeAsText(Types type) -> char *const;

    // ---------------------------------------------------------------------------
    // Prepare body to send:
    //
    // Header item \n
    // \n
    // content body
    inline auto RequestTransform(Request &request) -> void;

    // ---------------------------------------------------------------------------
    // Parse from string
    inline auto MakeRequest(const std::string &msg) -> Request;

    // ---------------------------------------------------------------------------
    inline auto typeAsText(Types type) -> char *const
    {
      char *result;
      switch (type)
      {
      case JSON:
        result = (char *)("application/json");
        break;
      case PLAIN:
        result = (char *)("text/plain");
        break;
      case BINARY:
        result = (char *)("application/octet-stream");
        break;
      default:
        result = (char *)("text/plain");
      }
      return result;
    }

    inline auto typeFromText(const std::string &type) -> Types
    {
      if (type.compare("application/json") == 0)
      {
        return JSON;
      }

      if (type.compare("application/octet-stream") == 0)
      {
        return BINARY;
      }

      return PLAIN;
    }
  } // namespace ContentType

  // ---------------------------------------------------------------------------
  struct Request
  {
    uint contentLength = 0;
    uint totalLength = 0;
    std::string content = "";
    std::string body = ""; // content with headers
    ContentType::Types contentType = ContentType::PLAIN;
  };

  // ---------------------------------------------------------------------------
  inline auto RequestTransform(Request &request) -> void
  {
    request.body = "Content-Type: " + std::string(ContentType::typeAsText(request.contentType));
    request.body += "\n";
    request.body += "\n";
    request.body += request.content;

    request.totalLength = request.body.size();
  }

  // ---------------------------------------------------------------------------
  inline auto MakeRequest(const std::string &msg, const ContentType::Types &type = ContentType::PLAIN) -> Request
  {
    Network::Request request;
    request.content = const_cast<char *>(msg.c_str());

    request.contentLength = request.content.size();
    Network::RequestTransform(request);

    return request;
  }

  // ---------------------------------------------------------------------------
  inline auto MakeResponse(const std::string &msg) -> Request
  {
    Network::Request response;

    const auto tokens = String::Split(msg, "\n\n");
    if (tokens.size() == 0)
    {
      return response;
    }

    const auto header = tokens.at(0);
    std::string content = "";
    if (tokens.size() > 1)
    {
      content = tokens.at(1);
    }

    response.contentLength = content.size();
    response.totalLength = msg.size();
    response.content = content;
    response.body = msg;

    // find content type
    {
      const auto _contentTypeTokens = String::Split(header, "Content-Type: ");
      if (_contentTypeTokens.size() == 2)
      {
        response.contentType = ContentType::typeFromText(_contentTypeTokens.at(1));
      }
    }

    return response;
  }
} // namespace mtEngine::Network
