#include "../include/app.hpp"

#include "Devices/Keyboard.hpp"
#include "Devices/Window.hpp"
#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Engine/Engine.hpp"
#include <iostream>
#include <memory>

namespace Editor {
  using namespace mtEngine;
  EditorApp::EditorApp(): App("Test") {

  }

  EditorApp::~EditorApp() {
    Graphics::Get()->SetRenderer(nullptr);
  }

  void EditorApp::Start() {
    Graphics::Get()->SetRenderer(std::make_unique<EditorRender>());
    Keyboard::Get()->OnKey().Add([](Key key, InputAction action, InputMod mod) {
      if(action == InputAction::Press && key == Key::F10) {
        Engine::Get()->RequestClose();
      } 
    });
  }

  void EditorApp::Update()
  {
  }
}
