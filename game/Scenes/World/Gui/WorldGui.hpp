#pragma once

#include "Guis/Imgui.hpp"
#include "Scenes/Scenes.hpp"

using namespace mtEngine;

namespace Game
{
  class WorldGui
  {
  public:
    WorldGui();

    void Window();

    void PlayerInfoDock();

    void Row();
  };
} // namespace Game
