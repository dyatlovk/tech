#pragma once

#include "Devices/Window.hpp"
#include "Engine/Log.hpp"

#include "Graphics/Graphics.hpp"
#include "Guis/Gui.hpp"
#include "Guis/Console.hpp"
#include "Imgui.hpp"

namespace mtEngine {
  using FontsStack = std::map<std::string, ImFont *>;
  constexpr std::string_view FONT_MAIN = "main";
  constexpr std::string_view FONT_MONO = "mono";

  class Gui : public Module::Registrar<Gui>
  {
    inline static const bool Registered = Register(Stage::Render, Requires<Graphics>()); 
    public:
      Gui();
      ~Gui();

      void Start();
      void NewFrame();
      void BeforeUpdate() override;
      void Update() override;
      void AfterUpdate() override;
      void Render();
      bool IsStarted() { return started; }
      void SetStarted() { started = true; }
      ImFont *GetFont(const std::string &name);
      void SetGui(std::unique_ptr<Gui> &&gui) { this->gui = std::move(gui); };

      Gui *GetGui() const { return gui.get(); }

      Console *GetConsole() { return console.get(); }
    private:
      void Shutdown() override;
      void LoadFont(const std::string &name, const std::string &path);
      bool started = false;
      std::unique_ptr<Console> console;
      bool showDemo = false;
      FontsStack fonts;
      std::unique_ptr<Gui> gui;
  };
}
