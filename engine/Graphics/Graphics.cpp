#include "Graphics.hpp"

namespace mtEngine {
  Graphics::Graphics() = default;

  Graphics::~Graphics()
  {
    renderer = nullptr;
  };

  void Graphics::Update()
  {
    if (!renderer->started) {
      renderer->Start();
      renderer->started = true;
    }

    renderer->BeforeUpdate();
    renderer->Update();
    renderer->AfterUpdate();
  }
}
