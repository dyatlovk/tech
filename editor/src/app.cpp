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
    Graphics::Get()->SetGui(std::make_unique<Gui>());

    std::string p(RESOURCES);
    Input::Get()->LoadScheme(p + "/Editor/keysmap.ini");
    static State state;

    States::Get()->OnState().Add([](State st) { 
      state = st; 
      std::cout << "state change: " << States::ToString(state) << std::endl;
    });
    States::Get()->Set(State::GUI);
   
    Input::Get()->GetButton("GUI", "Exit")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::GUI) return;
      if(InputAction::Press == action) Engine::Get()->RequestClose();
    });
    
    Input::Get()->GetButton("GUI", "Fullscreen")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::GUI) return;
      if(InputAction::Press == action) Window::Get()->MaximizeToggle();
    });
    
    Input::Get()->GetButton("GUI", "Player")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::GUI) return;
      if(InputAction::Press == action) States::Get()->Set(State::Player);
    });
    
    Input::Get()->GetButton("Player", "GUI")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::Player) return;
      if(InputAction::Press == action) States::Get()->Set(State::GUI);
    });
    
    Input::Get()->GetButton("Player", "Inventory")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::Player) return;
//       if(InputAction::Press == action) States::Get()->Set(State::GUI);
    });
    
    Input::Get()->GetButton("Inventory", "Player")->OnButton().Add([](InputAction action, InputMod mod) {
      if(state != State::GUI) return;
//       if(InputAction::Press == action) States::Get()->Set(State::Player);
    });
  }

  void EditorApp::Update()
  {
  }
}
