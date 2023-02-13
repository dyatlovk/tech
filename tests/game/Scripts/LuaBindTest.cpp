#include "Scripts/LuaBind.hpp"

#include <gtest/gtest.h>

#include "Config.hpp"

namespace Game::LuaBind
{
  class LuaBindFixture : public ::testing::Test
  {
  protected:
    LuaBindFixture() = default;
    ~LuaBindFixture() override = default;

    auto SetUp() -> void override
    {
      const std::string r(GameTests::ROOT_DIR);
      lua = Lua::Init();
      lua->GetState()->open_libraries(sol::lib::base, sol::lib::package, sol::lib::os);
      lua->SetPackageRoot(r + "/Fixtures/lua/");
    }

    std::unique_ptr<Lua> lua;
  };

  class TestRegister
  {
  public:
    TestRegister() {}
    ~TestRegister() {}

    auto foo() -> int { return 4; }
  };

  TEST_F(LuaBindFixture, init)
  {
    lua->Execute("game.lua");
    int exitCode = Lua::Get()->GetState()->get<int>("testExitCode");
    EXPECT_EQ(1, exitCode);
  }

  TEST_F(LuaBindFixture, badLuaCode)
  {
    lua->Execute("bad.lua");
    int exitCode = Lua::Get()->GetState()->get_or("testExitCode", 0);
    EXPECT_EQ(0, exitCode);
  }

  TEST_F(LuaBindFixture, runFunction)
  {
    lua->Execute("function.lua");
    lua->RunFunction("onTest");
    int exitCode = Lua::Get()->GetState()->get<int>("testExitCode");
    EXPECT_EQ(1, exitCode);
  }

  TEST_F(LuaBindFixture, registerClass)
  {
    lua->Register<TestRegister>("Test").set("foo", &TestRegister::foo);
    lua->Execute("register.lua");
    int exitCode = lua->GetState()->get<int>("testExitCode");
    EXPECT_EQ(1, exitCode);
  }

  TEST_F(LuaBindFixture, registerWithNamespace)
  {
    lua->Register<TestRegister>("Utils", "Test").set("foo", &TestRegister::foo);
    lua->Execute("namespace.lua");
    int exitCode = lua->GetState()->get<int>("testExitCode");
    EXPECT_EQ(1, exitCode);
  }
} // namespace Game::LuaBind
