#include "app.hpp"
#include "Graphics/Graphics.hpp"
#include "Render/GameRender.hpp"
#include "Utils/String.hpp"

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
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    CVars::Get()->Add("app", "command_1", {"45"}, "App command 1", "int", [](CVarParam &args, Input &input, bool &isValid) {
      // validate updated values
      isValid = true;
    });
    CVars::Get()->Add("app", "command_2", {"abc"}, "App command 2", "char", [](CVarParam &args, Input &input, bool &isValid) {
      // validate updated values
      isValid = true;
    });
    CVars::Get()->Add("test", "com", {"10"}, "App test command", "int", [](CVarParam &args, Input &input, bool &isValid) {
      // validate updated values
      isValid = true;
    });
  }

  void GameApp::BeforeUpdate() {
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
  }
}
