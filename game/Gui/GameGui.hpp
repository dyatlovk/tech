#pragma once

#include "Guis/Gui.hpp"
#include "Engine/Engine.hpp"

namespace Game
{
  class GameGui
  {
    public:
      GameGui();

      void Update();

      void Stats();

      void Debug();
    private:
      bool showStats = true;
      bool showUIDebug = false;
  };
}
