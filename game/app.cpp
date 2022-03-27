#include "app.hpp"
#include "Render/GameRender.hpp"
#include "Utils/String.hpp"

namespace Game {
  using namespace mtEngine;
  GameApp::GameApp(): App("Game") {
  }

  GameApp::~GameApp() {
    Graphics::Get()->SetRenderer(nullptr);
    Scenes::Get()->SetScene(nullptr);
    Gui::Get()->SetGui(nullptr);
  }

  void GameApp::Start() {
    PLOGD << "app start";
    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Game/keysmap.ini");
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    Scenes::Get()->SetScene(std::make_unique<MainMenu>());
    Gui::Get()->SetGui(std::make_unique<GameGui>());
    Gui::Get()->Start();

    Keyboard::Get()->OnKey().Add([](Key key, InputAction action, InputMod mods) {
    auto main = dynamic_cast<MainMenu *>(Scenes::Get()->GetScene());
    auto world = dynamic_cast<World *>(Scenes::Get()->GetScene());
    auto console = Gui::Get()->GetConsole()->IsVisible();
      if(console) return;
      if(main) {
        if(action == InputAction::Press && Key::Enter == key) {
          Scenes::Get()->Reload(std::make_unique<World>());
          return;
        }
      }
      if(world) {
        if(action == InputAction::Press && Key::Enter == key) {
          Scenes::Get()->Reload(std::make_unique<MainMenu>());
          return;
        }
      }
    });
  }

  void GameApp::BeforeUpdate() {
    Gui::Get()->NewFrame();
    Gui::Get()->Update();
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
    Gui::Get()->Render();
  }
}
