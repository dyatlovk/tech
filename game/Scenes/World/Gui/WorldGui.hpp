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

    void RowLeft();
    void RowRight();

    void Inventory();

    // sizeX, sizeY: unit Size of grid
    void AddItem(ImVec2 pos, const std::string &imgName, int sizeX, int sizeY, bool hovered = false);

  private:
    float padding = 10.0f;
    void CharacterItem();
    void Weapons();
    void Items();
    ImVec2 panelCursor;
    ImVec2 hudCursor;
    ImVec2 itemUnitSize = {60, 60};
  };
} // namespace Game
