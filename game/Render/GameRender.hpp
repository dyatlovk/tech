#pragma once

#include "Graphics/Renderer.hpp"
#include "../States/GameStates.hpp"
#include "../Gui/GameGui.hpp"

using namespace mtEngine;

namespace Game {
  class GameRender : public Renderer {
    public:
      GameRender(); 
      ~GameRender(); 

      void Start() override;
      void Update() override;
    private:
      std::unique_ptr<GameGui> GameUI;
      int image_width      = 0;
      int image_height     = 0;
      GLuint image_texture = 0;

      bool showHelp = true;
  };
}
