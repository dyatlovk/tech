#include "EditorRender.hpp"
#include "Devices/Window.hpp"
#include "Graphics/Graphics.hpp"
#include <iostream>
#include "States/States.hpp"

using namespace mtEngine;

namespace Editor {

  EditorRender::EditorRender() {
    std::cout << "start editor renderer" << std::endl;
  };

  EditorRender::~EditorRender() = default;

  void EditorRender::Start()
  {
    std::cout << "render start" << std::endl;
  }
 
  void EditorRender::Update()
  {
    bool static show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);
  }
}
