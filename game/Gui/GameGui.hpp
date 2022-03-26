#pragma once

#include "Guis/Gui.hpp"
#include "../States/GameStates.hpp"

namespace Game
{
  class GameGui
  {
    public:
      GameGui();
      ~GameGui();

      void Inventory();

      void Info();

      void Help(bool open);
  };
}
