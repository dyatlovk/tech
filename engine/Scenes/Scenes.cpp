#include "Scenes.hpp"

namespace mtEngine {
  Scenes::Scenes() {};

  void Scenes::Update()
  {
    if(!scene) return;

    if(!scene->started) {
      scene->Start();
      scene->started = true;
    }
      
    scene->Update();
  }
}
