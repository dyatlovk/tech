#pragma once

#include "Devices/Window.hpp"
#include "Engine/Log.hpp"

#include "Guis/Gui.hpp"
#include "Guis/Console.hpp"
#include "Imgui.hpp"

namespace mtEngine {
  using FontsStack = std::map<std::string, ImFont *>;
  constexpr std::string_view FONT_MAIN = "main";
  constexpr std::string_view FONT_MONO = "mono";

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
      ImFont *GetFont(const std::string &name);

      Console *GetConsole() { return console.get(); }
    private:
      void Shutdown();
      void LoadFont(const std::string &name, const std::string &path);
      bool started = false;
      std::unique_ptr<Console> console;
      bool showDemo = false;
      FontsStack fonts;
  };
}
