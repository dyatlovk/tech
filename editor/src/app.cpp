#include "../include/app.hpp"

#include "Devices/Keyboard.hpp"
#include "Devices/Window.hpp"
#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Engine/Engine.hpp"
#include <array>
#include <iostream>
#include <memory>

namespace Editor {
  using namespace mtEngine;
  EditorApp::EditorApp(): App("Test") {
    std::cout << "start editor" << std::endl;
  }

  EditorApp::~EditorApp() {
    Graphics::Get()->SetRenderer(nullptr);
  }

  void EditorApp::Start() {
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<EditorRender>());
    Window::Get()->OnSize().Add([](std::array<int, 2> size) {
      std::cout << "window resized {" << size[0] << ":" << size[1] << "}" << std::endl;
    });
    Keyboard::Get()->OnKey().Add([](Key key, InputAction action, InputMod mod) {
      if(action == InputAction::Press && key == Key::F10) {
        Engine::Get()->RequestClose();
      } 
      if(action == InputAction::Press && key == Key::F) {
        Window::Get()->MaximizeToggle();
      }
    });
  }

  void EditorApp::Update()
  {
  }
}
