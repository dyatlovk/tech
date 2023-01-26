#include "app.hpp"

#include "Guis/Font.hpp"
#include "Guis/IconsFontAwesome6.h"
#include "Inputs/Input.hpp"
#include "Render/GameRender.hpp"

namespace Game
{
  using namespace mtEngine;
  GameApp::GameApp()
      : App("Game")
      , socketClient(ClientSocket::Init())
      , commands(std::make_unique<AppCommands>())
  {
  }

  GameApp::~GameApp()
  {
    Graphics::Get()->SetRenderer(nullptr);
    mtEngine::Scenes::Get()->SetScene(nullptr);
    ClientSocket::CloseConnection();
    commands = nullptr;
    PLOGI << "app terminated";
  }

  void GameApp::Start()
  {
    PLOGD << "app start";
    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Game/keysmap.ini");

    ImFontConfig config;
    config.GlyphMinAdvanceX = 17.0f;
    static const ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    Font::Load("icons", p + "/Game/fonts/fa-solid-900.ttf", 20.0f, &config, icon_ranges);
    Font::Load("ui_bold", p + "/Game/fonts/Roboto-Bold.ttf", 17.0f, nullptr, nullptr);

    Window::Get()->SetPositionOnCenter();
    Graphics::Get()->SetRenderer(std::make_unique<GameRender>());
    mtEngine::Scenes::Get()->SetScene(std::make_unique<MainMenu>());

    commands->LoadScene();
    commands->ResourceLoad();
    commands->ResourceInfo();
    commands->ResourcesGet();
    commands->ResourceRemove();

    ServerSocket::Get()->emit("on app");
  }

  void GameApp::BeforeUpdate() {}

  void GameApp::Update() {}

  void GameApp::AfterUpdate()
  {
    if (gameGui == nullptr)
    {
      gameGui = std::make_unique<GameGui>();
    }
    gameGui->Stats();
    gameGui->Debug();
  }
} // namespace Game
