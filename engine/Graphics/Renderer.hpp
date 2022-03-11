#pragma once

#include "Devices/Window.hpp"
#include "Engine/Module.hpp"

namespace mtEngine {
  class Renderer  {
    friend class Graphics;
    public:
      Renderer() = default;

      virtual ~Renderer() = default;

      virtual void Start() = 0;
      virtual void Update() = 0;

      virtual void BeforeUpdate()
      {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      };

      virtual void AfterUpdate()
      {
        glfwSwapBuffers(Window::Get()->GetWindow());
      };

    private:
      bool started = false;
  };
}
