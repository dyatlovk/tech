#pragma once

#include "Scenes/Scene.hpp"
namespace Game {
  class GameScene : public mtEngine::Scene {
    public:
      GameScene();

      void Start() override;
      void Update() override;

      bool IsPaused() const override { return false; }
  };
}
