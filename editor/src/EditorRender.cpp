#include "EditorRender.hpp"
#include "Devices/Window.hpp"
#include "Graphics/Graphics.hpp"
#include <iostream>

using namespace mtEngine;

namespace Editor {

  EditorRender::EditorRender() {
    std::cout << "start editor renderer" << std::endl;
  };

  EditorRender::~EditorRender() = default;

  void EditorRender::Start()
  {
  }
 
  void EditorRender::Update()
  {
    bool static show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
  }
}
