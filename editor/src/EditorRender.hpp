#pragma once

#include <Graphics/Renderer.hpp>
#include <memory>
  
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
