#pragma once

#include "Guis/Imgui.hpp"
#include "Scenes/Scenes.hpp"
#include "Scenes/World/Gui/HUD/HUDLayout.hpp"

using namespace mtEngine;

namespace Game
{
  class WorldGui
  {
  public:
    WorldGui();

    void PlayerInfo();

    void Inventory();

    // sizeX, sizeY: unit Size of grid
    void AddItem(ImVec2 pos, const std::string &imgName, int sizeX, int sizeY, bool hovered = false) const;

  private:
    float padding = 10.0f;
    void CharacterItem();
    void Weapons() const;
    void Items() const;
    ImVec2 panelCursor;
    ImVec2 hudCursor;
    ImVec2 itemUnitSize = {60, 60};

  private:
    std::shared_ptr<HUDLayout> hudLayout;
    int health = 100;
    int armor = 100;
    int power = 100;
  };
} // namespace Game
