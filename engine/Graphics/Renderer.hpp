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

    private:
      bool started = false;
  };
}
