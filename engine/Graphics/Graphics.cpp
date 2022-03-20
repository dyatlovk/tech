#include "Graphics.hpp"

namespace mtEngine {
  Graphics::Graphics()
  {
    gui = std::make_unique<Gui>();
  };

  Graphics::~Graphics() = default;

  void Graphics::Shutdown()
  {
    gui = nullptr;
    PLOGD << "Graphics shutdown";
  }

  void Graphics::Update()
  {
    if (!renderer->started) {
      renderer->Start();
      renderer->started = true;
    }

    if(!gui->IsStarted()) {
      gui->Start();
      gui->SetStarted();
    }

    renderer->BeforeUpdate();
    gui->NewFrame();
    renderer->Update();
    renderer->AfterUpdate();
    gui->Render();
  }
}
