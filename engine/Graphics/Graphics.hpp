#pragma once

#include "Devices/Window.hpp"
#include "Engine/Module.hpp"
#include "Graphics/Renderer.hpp"
#include "Guis/Gui.hpp"
#include <algorithm>
#include <memory>

namespace mtEngine {
  class Graphics : public Module::Registrar<Graphics> {
    inline static const bool Registered = Register(Stage::Render, Requires<Window>()); 
    public:
      Graphics();

      ~Graphics();

      void Update() override;

      void SetRenderer(std::unique_ptr<Renderer> &&renderer) { this->renderer = std::move(renderer); }
      void SetGui(std::unique_ptr<Gui> &&gui) { this->gui = std::move(gui); };

      Renderer *GetRenderer() const { return renderer.get(); }

      Gui *GetGui() const { return gui.get(); }

    private:
      std::unique_ptr<Renderer> renderer;
      std::unique_ptr<Gui> gui;
  };
}