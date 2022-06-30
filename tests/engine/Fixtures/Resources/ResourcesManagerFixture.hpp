#pragma once

#include <gtest/gtest.h>
#include <memory>

#include "Resources/ResourcesManager.hpp"
#include "ResourceFixture.hpp"

namespace EngineTest
{
  class ResourcesManagerTest : public ::testing::Test
  {
  protected:
    ResourcesManagerTest() = default;
    ~ResourcesManagerTest() override = default;

    void SetUp() override
    {
      instance = std::make_shared<mtEngine::ResourcesManager>();
      resourse = std::make_shared<ResourceTest>();
    }

    std::shared_ptr<mtEngine::ResourcesManager> instance;
    std::shared_ptr<ResourceTest> resourse;
  };
} // namespace EngineTest
