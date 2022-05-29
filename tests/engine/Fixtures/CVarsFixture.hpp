#pragma once
#include <gtest/gtest.h>
#include <Engine/CVars.hpp>

namespace EngineTest
{
  class CVarsTest : public ::testing::Test
  {
  protected:
    CVarsTest() = default;
    ~CVarsTest() override = default;

    void SetUp() override
    {
      instance = mtEngine::CVars::Init();
      using CVarParam = std::vector<std::string>;
      using Input = std::vector<std::string>;
      instance->Add("group", "test", {}, "Group test", "group test description", [](CVarParam &args, Input &input, bool &isValid) {
      }, "var", false);
    }

    std::unique_ptr<mtEngine::CVars> instance;
  };
} // namespace EngineTest
