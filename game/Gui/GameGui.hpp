#pragma once

#include "Guis/Gui.hpp"
#include "../States/GameStates.hpp"

namespace Game
{
  class GameGui: public mtEngine::Gui
  {
    public:
      GameGui();

      void Update();

      void Inventory();

      void Info();

      void Help(bool open);
  };
}
