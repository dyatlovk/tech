#pragma once

#include "Devices/Window.hpp"
#include "Engine/Log.hpp"

#include "Guis/Gui.hpp"
#include "Guis/Console.hpp"
#include "Imgui.hpp"

namespace mtEngine {
  class Gui
  {
    public:
      Gui();
      ~Gui();

      void Start();
      void NewFrame();
      void Update();
      void Render();
      bool IsStarted() { return started; }
      void SetStarted() { started = true; }

      Console *GetConsole() { return console.get(); }
    private:
      void Shutdown();
      bool started = false;
      std::unique_ptr<Console> console;
  };
}
