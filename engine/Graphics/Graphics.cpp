#include "Graphics.hpp"

namespace mtEngine {
  Graphics::Graphics() = default;

  Graphics::~Graphics()
  {
    renderer = nullptr;
    gui = nullptr;
  };

  void Graphics::Update()
  {
    if(!gui->started) {
      gui->Start();
      gui->started = true;
    }

    gui->BeforeUpdate();
    gui->Update();

    if (!renderer->started) {
      renderer->Start();
      renderer->started = true;
    }

    renderer->BeforeUpdate();
    renderer->Update();
    gui->AfterUpdate();
    renderer->AfterUpdate();
  }
}
