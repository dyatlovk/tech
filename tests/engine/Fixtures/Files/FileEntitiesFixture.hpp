#pragma once

#include <gtest/gtest.h>

#include "Files/FileEntities.hpp"

namespace EngineTest
{
  class FileEntitiesFixture : public ::testing::Test
  {
  protected:
    FileEntitiesFixture() = default;

    ~FileEntitiesFixture() override = default;

    void SetUp() override { instance = mtEngine::Files::FileEntities::Create(jsonFile); }

    std::shared_ptr<mtEngine::Files::FileEntities> instance;
    const std::string root = "../../..";
    const std::filesystem::path jsonFile = root + "/tests/engine/Fixtures/Files/entities.json";
  };
} // namespace EngineTest
