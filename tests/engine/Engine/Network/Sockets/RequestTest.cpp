#include "Network/Request.hpp"

#include <gtest/gtest.h>

namespace RequestTest
{
  using namespace mtEngine;
  TEST(RequestTest, TypeAsText)
  {
    EXPECT_EQ("application/json", Network::ContentType::typeAsText(Network::ContentType::JSON));
    EXPECT_EQ("text/plain", Network::ContentType::typeAsText(Network::ContentType::PLAIN));
    EXPECT_EQ("application/octet-stream", Network::ContentType::typeAsText(Network::ContentType::BINARY));
  }

  TEST(RequestTest, TypeFromText)
  {
    EXPECT_EQ(Network::ContentType::JSON, Network::ContentType::typeFromText("application/json"));
    EXPECT_EQ(Network::ContentType::PLAIN, Network::ContentType::typeFromText("text/plain"));
    EXPECT_EQ(Network::ContentType::BINARY, Network::ContentType::typeFromText("application/octet-stream"));
  }

  TEST(RequestTest, MakeRequest)
  {
    const std::string msg = "msg";
    const std::string body = "Content-Type: text/plain\n\n" + msg;
    const auto request = Network::MakeRequest(msg);

    EXPECT_EQ(msg, request.content);

    EXPECT_EQ(msg.size(), request.contentLength);
    EXPECT_EQ(body.size(), request.totalLength);
    EXPECT_EQ(Network::ContentType::PLAIN, request.contentType);

    EXPECT_EQ(body, request.body);
  }

  TEST(RequestTest, MakeResponse)
  {
    std::string ua = std::string(ServerSocket::USER_AGENT) + "/" + std::string(VERSION);
    const std::string msg = "msg";
    const std::string body = "Content-Type: text/plain\n\n" + msg;

    const auto response = Network::MakeResponse(body);
    EXPECT_EQ(msg.size(), response.contentLength);
    EXPECT_EQ(body.size(), response.totalLength);
    EXPECT_EQ(msg, response.content);
    EXPECT_EQ(body, response.body);
    EXPECT_EQ(Network::ContentType::PLAIN, response.contentType);
  }

  TEST(RequestTest, JSON)
  {
    std::string ua = std::string(ServerSocket::USER_AGENT) + "/" + std::string(VERSION);
    const std::string msg = "{'json': 'test'}";
    const std::string body = "Content-Type: application/json\n\n" + msg;
    const auto request = Network::MakeRequest(msg, Network::ContentType::JSON);
    EXPECT_EQ(msg, request.content);
  }

} // namespace RequestTest
