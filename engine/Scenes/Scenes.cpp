#include "Scenes.hpp"

#include "Engine/Engine.hpp"

namespace mtEngine {
  Scenes::Scenes() {};

  void Scenes::Update()
  {
    if(!scene) return;

    if(!scene->started) {
      scene->Start();
      scene->started = true;
    }

    scene->BeforeUpdate();
    scene->Update();
    scene->AfterUpdate();
  }

  void Scenes::Shutdown()
  {
    scene->Shutdown();
    PLOGD << "scenes shutdown";
  }
}
