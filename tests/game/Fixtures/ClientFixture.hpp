#pragma once
#include <memory>

#include <Scenes/World/Client/Communication.hpp>

#include "Config.hpp"
#include "Files/File.hpp"
#include "gtest/gtest.h"

namespace WorldTest
{
  using json = nlohmann::json;
  using namespace mtEngine;
  class ClientTest : public ::testing::Test
  {
  protected:
    ClientTest() = default;

    ~ClientTest() override = default;

    auto SetUp() -> void override
    {
      std::string root(GameTests::ROOT_DIR);
      const auto file = std::make_unique<File>();
      file->Load(root + "/Fixtures/scene_info.json");
      _str = file->GetBuffer();

      const auto fileObject = std::make_unique<File>();
      fileObject->Load(root + "/Fixtures/object_info.json");
      _str_object_info = fileObject->GetBuffer();
    }

    std::string _str;
    std::string _str_object_info;
  };
} // namespace WorldTest
