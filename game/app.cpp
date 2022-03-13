#include "app.hpp"
#include "Devices/Window.hpp"
#include "Graphics/Graphics.hpp"
#include "Render/GameRender.hpp"

namespace Game {
  using namespace mtEngine;
  GameApp::GameApp(): App("Game") { }
  
  GameApp::~GameApp() {
    Graphics::Get()->SetRenderer(nullptr);
    Graphics::Get()->SetGui(nullptr);
  }
  
  void GameApp::Start() {
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    Graphics::Get()->SetGui(std::make_unique<Gui>());
  }

  void GameApp::Update() { }
}
