#pragma once

#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_impl_opengl3.h"

#include <Graphics/Renderer.hpp>
  
using namespace mtEngine;

namespace Editor {
  class EditorRender: public Renderer {
    public:
      EditorRender();
      ~EditorRender();

      void Start() override;
      void Update() override;
  };
}
