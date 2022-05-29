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
}
