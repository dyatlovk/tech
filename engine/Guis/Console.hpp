#pragma once

#include "Inputs/Input.hpp"

#include "Imgui.hpp"

namespace mtEngine {
  class Console
  {
    public:
      static constexpr float HEIGHT_PERCENT = 45.0f;
      Console();

      void Start();
      void Render();
      void Update();

      bool ToggleVisible() { visible = !visible; return visible; };
      bool IsVisible() { return visible; };
    private:
      bool visible = false;
      bool down = false;
      bool up = false;

      void KeyboardScroll(bool scrollDown = false);
  };
}
