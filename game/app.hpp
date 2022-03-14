#pragma once

#include "Engine/App.hpp"
#include "States/GameStates.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/Scenes.hpp"

namespace Game {
  class GameApp : public mtEngine::App {
    public:
      GameApp();
      ~GameApp();
             
      void Start() override;
      void Update() override;
    };
}
