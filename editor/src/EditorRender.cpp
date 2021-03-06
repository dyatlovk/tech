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
    bool static show_demo_window = false;
    if(States::Get()->Current() == EnumStates::GUI) {
      glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    }
    if(States::Get()->Current() == EnumStates::Player) {
      glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    }
  }
}
