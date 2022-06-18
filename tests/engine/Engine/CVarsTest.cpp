#include "Fixtures/CVarsFixture.hpp"

#include "gtest/gtest.h"

namespace EngineTest
{
  TEST_F(CVarsTest, AddVariable)
  {
    auto _command = instance->getList().begin()->second;
    EXPECT_EQ("group", instance->getList().begin()->first);
    EXPECT_EQ("test", _command.begin()->name);
    EXPECT_EQ("Group test", _command.begin()->description);
    EXPECT_EQ("group test description", _command.begin()->help);
  }

  TEST_F(CVarsTest, PreventAddVariableTwice)
  {
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    instance->Add("group", "test", {}, "Group test", "group test description", [](CVarParam &args, Input &input, bool &isValid) {
    }, "var", false);

    auto _commands = instance->getList();
    EXPECT_EQ(1, _commands.size());
  }

  TEST_F(CVarsTest, GroupNotFound)
  {
    instance->Exec("notfound test 1");
    auto _commands = instance->getList();
    EXPECT_EQ(-1, callback);
  }

  TEST_F(CVarsTest, ClearStorage)
  {
    instance->ClearStorage();

    auto _commands = instance->getList();
    EXPECT_EQ(0, _commands.size());
  }

  TEST_F(CVarsTest, ExecCallbackValid)
  {
    instance->Exec("group test 1");
    EXPECT_EQ(1, callback);
  }

  TEST_F(CVarsTest, ExecCallbackNotValid)
  {
    instance->Exec("group test 0");
    EXPECT_NE(1, callback);
  }

  TEST_F(CVarsTest, RemoveGroup)
  {
    instance->RemoveGroup("group");
    auto cmds = instance->getList();
    EXPECT_EQ(0, cmds.size());
  }
}
