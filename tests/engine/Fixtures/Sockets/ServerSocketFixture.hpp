#pragma once
#include <gtest/gtest.h>

#include "Network/Sockets/ServerSocket.hpp"

namespace EngineTest
{
  class ServerSocketFixture : public ::testing::Test
  {
  protected:
    ServerSocketFixture() = default;
    ~ServerSocketFixture() override = default;

    void SetUp() override { instance = mtEngine::ServerSocket::Init(); }

    std::unique_ptr<mtEngine::ServerSocket> instance;
  };
} // namespace EngineTest
