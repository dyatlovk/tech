#pragma once

#include <Engine/App.hpp>
#include "Graphics/Graphics.hpp"
#include "Gui/GameGui.hpp"
#include "Scenes/MainMenu/MainMenu.hpp"
#include "Scenes/World/World.hpp"
#include "States/GameStates.hpp"
#include "Utils/ThreadPool.hpp"

namespace Game
{
  class GameApp : public mtEngine::App
  {
  public:
    GameApp();
    ~GameApp() override;

    void Start() override;
    void BeforeUpdate() override;
    void Update() override;
    void AfterUpdate() override;
  private:
    std::unique_ptr<GameGui> gameGui;
    std::unique_ptr<Scene> scene;
  };
} // namespace Game
