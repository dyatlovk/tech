#pragma once

#include "Inputs/Input.hpp"
#include "States/EnumStates.hpp"
#include "States/States.hpp"

#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_stdlib.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"
#include "third_party/imgui/imgui_internal.h"

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
