#pragma once

#include "Engine/App.hpp"

namespace Game {
  class GameApp : public mtEngine::App {
    public:
      GameApp();
      ~GameApp();
             
      void Start() override;
      void Update() override;
    };
}
