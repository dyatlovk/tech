#pragma once

#include <Engine/App.hpp>

#include "Commands/AppCommands.hpp"
#include "Graphics/Graphics.hpp"
#include "Gui/GameGui.hpp"
#include "Scenes/MainMenu/MainMenu.hpp"
#include "Scenes/World/World.hpp"
#include "Scripts/LuaBind.hpp"
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
    std::unique_ptr<AppCommands> commands;
    std::unique_ptr<Lua> m_lua;
  };
} // namespace Game
