#pragma once

#include "Scenes/Scene.hpp"
namespace Game {
  class GameScene : public mtEngine::Scene {
    public:
      GameScene();
      ~GameScene();

      void Start() override;
      void BeforeUpdate() override;
      void Update() override;
      void AfterUpdate() override;

      bool IsPaused() const override { return false; }
  };
}
