#include "../include/app.hpp"

#include "Config.hpp"
#include "Devices/Window.hpp"
#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include "Engine/Engine.hpp"
#include "Inputs/Input.hpp"
#include "States/States.hpp"

namespace Editor {
  using namespace mtEngine;
  EditorApp::EditorApp(): App("Test") {
    std::cout << "start editor" << std::endl;
  }

  EditorApp::~EditorApp() {
    Graphics::Get()->SetRenderer(nullptr);
  }

  void EditorApp::Start() {
    std::cout << "app start" << std::endl;
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<EditorRender>());

    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Editor/keysmap.ini");
    static int state;

    States::Get()->OnState().Add([](int st) { 
      state = st; 
      std::cout << "state change: " << States::ToString(state) << std::endl;
    });
    States::Get()->Set(EnumStates::GUI);
  }
  
  void EditorApp::BeforeUpdate()
  {
  }

  void EditorApp::Update()
  {
  }
  
  void EditorApp::AfterUpdate()
  {
  }
}
