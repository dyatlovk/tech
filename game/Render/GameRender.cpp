#include "GameRender.hpp"
#include "Guis/Gui.hpp"
#include "Config.hpp"

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
  }

  void GameRender::Update()
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  }
}
