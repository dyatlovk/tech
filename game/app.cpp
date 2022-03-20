#include "app.hpp"
#include "Graphics/Graphics.hpp"
#include "Render/GameRender.hpp"

namespace Game {
  using namespace mtEngine;
  GameApp::GameApp(): App("Game") {
  }

  GameApp::~GameApp() {
    Graphics::Get()->SetRenderer(nullptr);
    Scenes::Get()->SetScene(nullptr);
  }

  void GameApp::Start() {
    PLOGD << "app start";
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    Scenes::Get()->SetScene(std::make_unique<GameScene>());
    CVars::Get()->Add<std::string>("app", "1", "1", "Default app");
  }

  void GameApp::BeforeUpdate() {
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
  }
}
