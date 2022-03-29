#include "app.hpp"
#include "Render/GameRender.hpp"
#include "Utils/String.hpp"
#include "Inputs/Input.hpp"

namespace Game {
  using namespace mtEngine;
  GameApp::GameApp(): App("Game") {
  }

  GameApp::~GameApp() {
    Graphics::Get()->SetRenderer(nullptr);
    Scenes::Get()->SetScene(nullptr);
    gameGui = nullptr;
  }

  void GameApp::Start() {
    PLOGD << "app start";
    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Game/keysmap.ini");
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    Scenes::Get()->SetScene(std::make_unique<MainMenu>());
    gameGui = std::make_unique<GameGui>();
  }

  void GameApp::BeforeUpdate() {
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
    gameGui->Stats();
    gameGui->Debug();
  }
}
