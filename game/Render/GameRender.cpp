#include "GameRender.hpp"

namespace Game {
  GameRender::GameRender()
  {

  }

  GameRender::~GameRender()
  {

  }

  void GameRender::Start()
  {

  }

  void GameRender::Update()
  {
    int state = States::Get()->Current();
    if(state == GameStates::MainMenu) {
      // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    if(state == GameStates::Player) {
      // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    }
    
    if(state == GameStates::Inventory) {
      // glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    }
    
    if(state == GameStates::PauseMenu) {
      // glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }
  }
}
