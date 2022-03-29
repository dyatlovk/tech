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

    void MessageDock();

    void PlayerInfoDock();

    void Items();
  };
} // namespace Game
