#include <filesystem>
#include <unistd.h>

#include "Fixtures/Sockets/ServerSocketFixture.hpp"

namespace EngineTest
{
  TEST_F(ServerSocketFixture, Init)
  {
    const auto isFileSocketExists = std::filesystem::exists(mtEngine::ServerSocket::SOCKET_PATH);
    EXPECT_TRUE(isFileSocketExists);
    ASSERT_NE(instance, nullptr);
  }

  TEST_F(ServerSocketFixture, StartListen)
  {
    instance->shutdown();
    const auto isFileSocketExists = std::filesystem::exists(mtEngine::ServerSocket::SOCKET_PATH);
    EXPECT_FALSE(isFileSocketExists);
  }

  TEST_F(ServerSocketFixture, Emit)
  {
    instance->emit("test");
    instance->OnRecieve().Add([&](std::string msg) { EXPECT_EQ("test", msg); });
  }
} // namespace EngineTest
