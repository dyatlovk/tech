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
    private:
      bool showStats = true;
  };
}
