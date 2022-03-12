#include "../include/app.hpp"

#include "Config.hpp"
#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Engine/Engine.hpp"
#include "Inputs/Input.hpp"

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

    std::string p(RESOURCES);
    Input::Get()->LoadScheme(p + "/keysmap.ini");
    Input::Get()->GetButton("Default", "Quit")->OnButton().Add([](InputAction action, InputMod mod) {
      if(InputAction::Press == action) {
        Engine::Get()->RequestClose();
      }
    });
    
    Input::Get()->GetButton("Default", "Fullscreen")->OnButton().Add([](InputAction action, InputMod mod) {
      if(InputAction::Press == action) {
        Window::Get()->MaximizeToggle();
      }
    });

    auto winSize = Window::Get()->GetSize();
    std::string title = "Demo[" + std::to_string(winSize[0]) + "x" + std::to_string(winSize[1]) + "]";
    Window::Get()->SetTitle(title);
    
    Window::Get()->OnSize().Add([](std::array<int, 2> size) {
      std::string title = "Demo[" + std::to_string(size[0]) + "x" + std::to_string(size[1]) + "]";
      Window::Get()->SetTitle(title);
    });
  }

  void EditorApp::Update()
  {
  }
}
