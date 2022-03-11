#include "../include/app.hpp"

#include "Devices/Keyboard.hpp"
#include "Devices/Window.hpp"
#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Engine/Engine.hpp"
#include "Guis/Gui.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <string>

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
    Graphics::Get()->SetGui(std::make_unique<Gui>());
    auto winSize = Window::Get()->GetSize();
    std::string title = "Demo[" + std::to_string(winSize[0]) + "x" + std::to_string(winSize[1]) + "]";
    Window::Get()->SetTitle(title);
    
    Window::Get()->OnSize().Add([](std::array<int, 2> size) {
      std::string title = "Demo[" + std::to_string(size[0]) + "x" + std::to_string(size[1]) + "]";
      Window::Get()->SetTitle(title);
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
