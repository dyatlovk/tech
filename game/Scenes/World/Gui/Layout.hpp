#pragma once

#include "Guis/Imgui.hpp"
#include "Utils/NonCopyable.hpp"

using namespace mtEngine;

namespace Game
{
  class WorldLayout : public NonCopyable
  {
  public:
    WorldLayout() = default;

    void Create();
  };
} // namespace Game
