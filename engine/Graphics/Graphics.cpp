#include "Graphics.hpp"

namespace mtEngine {
  Graphics::Graphics()
  {
    Shader::CreateDefault();
    PLOGI << "graphics constructor";
  };

  Graphics::~Graphics() = default;

  void Graphics::Shutdown()
  {
    PLOGD << "Graphics shutdown";
  }

  void Graphics::BeforeUpdate()
  {
    if(!renderer->started) return;
    renderer->BeforeUpdate();
  }

  void Graphics::Update()
  {
    if (!renderer->started) {
      renderer->Start();
      renderer->started = true;
    }

    renderer->Update();
    renderer->AfterUpdate();
  }
}
