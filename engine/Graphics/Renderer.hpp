#pragma once

#include "Devices/Window.hpp"

namespace mtEngine {
  class Renderer  {
    friend class Graphics;
    public:
      Renderer()
      {
        // gui = std::make_unique<Gui>();
      };

      virtual ~Renderer() = default;

      virtual void Start() = 0;
      virtual void Update() = 0;

      void BeforeUpdate()
      {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      };

      void AfterUpdate()
      {
      };

    private:
      bool started = false;
  };
}
