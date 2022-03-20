#pragma once

#include "Devices/Window.hpp"
#include "Engine/Log.hpp"

#include "Guis/Gui.hpp"
#include "Guis/Console.hpp"
#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_stdlib.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"
#include "third_party/imgui/imgui_internal.h"

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
