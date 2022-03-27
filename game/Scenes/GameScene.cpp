#include "GameScene.hpp"

using namespace mtEngine;

namespace Game {
  GameScene::GameScene() = default;

  GameScene::~GameScene() = default;

  void GameScene::Start()
  {
    PLOGD << "game scene started";
    gui = dynamic_cast<GameGui *>(Gui::Get()->GetGui());
  }

  void GameScene::BeforeUpdate()
  {
  }

  void GameScene::Update()
  {
    gui->Inventory();
    gui->Info();
  }

  void GameScene::AfterUpdate()
  {
  }

  void GameScene::Shutdown()
  {
    PLOGD << "game scene shutdown";
  }
}
