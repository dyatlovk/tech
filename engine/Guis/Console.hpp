#pragma once

#include "Inputs/Input.hpp"

#include "Imgui.hpp"

namespace mtEngine {
  class Console
  {
    public:
      Console();

      void Start();
      void Render();
      void Update();

      bool ToggleVisible() { visible = !visible; return visible; };
      bool IsVisible() { return visible; };
    private:
      bool visible = false;
  };
}
