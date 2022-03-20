#pragma once

#include "Scenes/Scene.hpp"
#include "../Gui/GameGui.hpp"
#include "Graphics/Graphics.hpp"

using namespace mtEngine;

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
