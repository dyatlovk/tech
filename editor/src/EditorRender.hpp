#pragma once

#include <Graphics/Renderer.hpp>
  
using namespace mtEngine;

namespace Editor {
  class EditorRender: public Renderer {
    public:
      EditorRender();

      void Start() override;
      void Update() override;
  };
}
