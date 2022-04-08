#include "app.hpp"
#include "Guis/Font.hpp"
#include "Render/GameRender.hpp"
#include "Utils/String.hpp"
#include "Inputs/Input.hpp"
#include "Guis/IconsFontAwesome6.h"

namespace Game {
  using namespace mtEngine;
  GameApp::GameApp(): App("Game") {
  }

  GameApp::~GameApp() {
    Graphics::Get()->SetRenderer(nullptr);
    Scenes::Get()->SetScene(nullptr);
    gameGui = nullptr;
  }

  void GameApp::Start() {
    PLOGD << "app start";
    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Game/keysmap.ini");
    
    ImFontConfig config; 
    config.GlyphMinAdvanceX = 17.0f;
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    Font::Load("icons", p + "/Game/fonts/fa-solid-900.ttf", 20.0f, &config, icon_ranges);
    Font::Load("ui_bold", p + "/Game/fonts/Roboto-Bold.ttf", 17.0f, nullptr, nullptr);
    
    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    Scenes::Get()->SetScene(std::make_unique<MainMenu>());
    gameGui = std::make_unique<GameGui>();
  }

  void GameApp::BeforeUpdate() {
  }

  void GameApp::Update() {
  }

  void GameApp::AfterUpdate() {
    gameGui->Stats();
    gameGui->Debug();
  }
}
