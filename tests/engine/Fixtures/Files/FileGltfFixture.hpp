#pragma once

#include <gtest/gtest.h>
#include "Files/FileGltf.hpp"

namespace EngineTest {
  class FileGltfFixture : public ::testing::Test
  {
  protected:
    FileGltfFixture() = default;

    ~FileGltfFixture() override = default;

    void SetUp() override
    {
      instance = mtEngine::Files::FileGltf::Create(gltfFile);
    }

    std::shared_ptr<mtEngine::Files::FileGltf> instance;
    const std::string root = "../../..";
    const std::filesystem::path gltfFile = root + "/tests/engine/Fixtures/Files/gltf.gltf";
  };
}
