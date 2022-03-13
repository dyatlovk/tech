#pragma once

#include "Graphics/Renderer.hpp"
using namespace mtEngine;

namespace Game {
  class GameRender : public Renderer {
    public:
      GameRender(); 
      ~GameRender(); 

      void Start() override;
      void Update() override;
  };
}
