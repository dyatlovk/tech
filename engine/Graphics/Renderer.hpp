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

      virtual void BeforeUpdate() = 0;

      void AfterUpdate()
      {
      
      };

    private:
      bool started = false;
  };
}
