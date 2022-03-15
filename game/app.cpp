#include "app.hpp"
#include "Config.hpp"
#include "Devices/Window.hpp"
#include "Graphics/Graphics.hpp"
#include "Render/GameRender.hpp"
#include "Inputs/Input.hpp"

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
    std::string p(RESOURCES);
    Input::Get()->LoadScheme(p + "/Game/keysmap.ini");

    static int state;
    States::Get()->OnState().Add([&](int st) {
      state = st;
      PLOGD << "On state: " << GameStates::ToString(state);
    });
    States::Get()->Set(GameStates::MainMenu);

    int listeners = 0;
    Input::Get()->GetButton("MainMenu", "Exit")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::MainMenu) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) Engine::Get()->RequestClose();
    });

    Input::Get()->GetButton("MainMenu", "New")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::MainMenu) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) States::Get()->Set(GameStates::Player);
    });

    Input::Get()->GetButton("MainMenu", "Fullscreen")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::MainMenu) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) Window::Get()->MaximizeToggle();
    });

    Input::Get()->GetButton("Player", "Inventory")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::Player) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) States::Get()->Set(GameStates::Inventory);
    });

    Input::Get()->GetButton("Inventory", "Player")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::Inventory) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) States::Get()->Set(GameStates::Player);
    });
    
    Input::Get()->GetButton("Inventory", "Close")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::Inventory) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) States::Get()->Set(GameStates::Player);
    });

    Input::Get()->GetButton("Player", "PauseMenu")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::Player) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }

      if(InputAction::Press == action) States::Get()->Set(GameStates::PauseMenu);
    });

    Input::Get()->GetButton("PauseMenu", "Player")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::PauseMenu) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }

      if(InputAction::Press == action) States::Get()->Set(GameStates::Player);
    });

    Input::Get()->GetButton("PauseMenu", "MainMenu")->OnButton().Add([&](InputAction action, InputMod mod) {
      if(state != GameStates::PauseMenu) return;
      ++listeners;
      if(listeners > 1) {
        listeners = 0;
        return;
      }
      if(InputAction::Press == action) States::Get()->Set(GameStates::MainMenu);
    });
  }

  void GameApp::BeforeUpdate() {
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
  }
}
