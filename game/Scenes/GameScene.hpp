#pragma once

#include "Scenes/Scenes.hpp"
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

      void Shutdown() override;
      virtual std::string GetName() const override { return name; };
    private:
      GameGui *gui;
      const std::string name = "main";
  };
}
