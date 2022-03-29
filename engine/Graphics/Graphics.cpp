#include "Graphics.hpp"

namespace mtEngine {
  Graphics::Graphics()
  {
  };

  Graphics::~Graphics() = default;

  void Graphics::Shutdown()
  {
    PLOGD << "Graphics shutdown";
  }

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
