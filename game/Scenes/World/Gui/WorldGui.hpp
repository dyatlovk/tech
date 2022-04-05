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

    void Inventory();

  private:
    float padding = 10.0f;
    void CharacterItem();
    void Weapons();
    void Items();
    ImVec2 panelCursor;
  };
} // namespace Game
