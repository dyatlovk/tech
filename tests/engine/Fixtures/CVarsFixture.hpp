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
      instance->Add("group", "test", {"1"}, "Group test", "group test description", [this](CVarParam &args, Input &input, bool &isValid) {
        if(input.empty()) {
          isValid = false;
          return;
        }
        callback = stoi(input.at(0));
        isValid = true;
      }, "var", false);
    }

    std::unique_ptr<mtEngine::CVars> instance;
    int callback = -1;
  };
} // namespace EngineTest
