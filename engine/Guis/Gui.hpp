#pragma once

#include "Graphics/Renderer.hpp"

#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"

namespace mtEngine {
  class Gui: public Renderer {
    public:
      Gui();
      ~Gui();

      void Start() override;

      void Update() override;

      void BeforeUpdate() override;
      void AfterUpdate() override;
  };
}
