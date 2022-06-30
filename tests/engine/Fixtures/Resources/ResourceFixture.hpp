#pragma once

#include "Resources/Resource.hpp"

namespace EngineTest
{
  class ResourceTest : public mtEngine::Resource
  {
  public:
    ResourceTest() = default;
    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(ResourceTest);
    }

    int checkFlag = 0;
  };
}
