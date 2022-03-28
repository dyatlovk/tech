#pragma once
#include "Guis/Imgui.hpp"
#include "Engine/Engine.hpp"
#include "../../World/World.hpp"

using namespace mtEngine;

namespace Game
{
  class MenuGui
  {
    public:
      MenuGui();

      void Update();

      void RenderList();
  };
} // namespace Game
