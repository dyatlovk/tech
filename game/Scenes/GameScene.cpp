#include "GameScene.hpp"

#include "Config.hpp"
#include "../States/GameStates.hpp"
#include "Engine/Engine.hpp"
#include "Inputs/Input.hpp"

using namespace mtEngine;

namespace Game {
  GameScene::GameScene() = default;

  GameScene::~GameScene() = default;

  void GameScene::Start()
  {
    PLOGD << "game scene started";
    
    States::Get()->Set(GameStates::MainMenu);
 
    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if(action != InputAction::Press) return; 
      int state = States::Get()->Current();

      // stop propagation other events
      if(Graphics::Get()->GetGui()->GetConsole()->IsVisible()) return;

      if(state == GameStates::MainMenu) {
        if(key == Key::F10) {
          Engine::Get()->RequestClose();
        }
        
        if(key == Key::Enter) {
          States::Get()->Set(GameStates::Player);
        }
      }

      if(state == GameStates::Player) {
        if(key == Key::I) {
          States::Get()->Set(GameStates::Inventory);
        }
        if(key == Key::F10) {
          States::Get()->Set(GameStates::MainMenu);
        }
      }
      
      if(state == GameStates::Inventory) {
        if(key == Key::I || key == Key::Escape) {
          States::Get()->Set(GameStates::Player);
        }
      }
    });
  }

  void GameScene::BeforeUpdate()
  {
  }

  void GameScene::Update()
  {
  }

  void GameScene::AfterUpdate()
  {
  }
}
