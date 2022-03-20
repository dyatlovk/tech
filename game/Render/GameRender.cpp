#include "GameRender.hpp"

namespace Game {
  GameRender::GameRender()
  {

  }

  GameRender::~GameRender()
  {
    PLOGD << "app render destruct";
  }

  void GameRender::Start()
  {
    GameUI = std::make_unique<GameGui>();
    PLOGD << "app render start";
  }

  void GameRender::Update()
  {
    GameUI->Inventory();
    GameUI->Info();
  }
}
