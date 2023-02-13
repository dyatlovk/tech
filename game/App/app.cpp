#include "app.hpp"

#include "Guis/Font.hpp"
#include "Guis/IconsFontAwesome6.h"
#include "Inputs/Input.hpp"
#include "Render/GameRender.hpp"
#include "Scripts/GameLog.hpp"

namespace Game
{
  using namespace mtEngine;
  using json = nlohmann::json;
  GameApp::GameApp()
      : App("Game")
      , commands(std::make_unique<AppCommands>())
      , m_lua(Lua::Init())
  {
  }

  GameApp::~GameApp()
  {
    Graphics::Get()->SetRenderer(nullptr);
    mtEngine::Scenes::Get()->SetScene(nullptr);
    commands = nullptr;
    Lua::Get()->RunFunction("onDestroy");
  }

  void GameApp::Start()
  {
    std::string p(RESOURCES);
    Input::Get()->LoadConfig(p + "/Game/keysmap.ini");

    Lua::Get()->GetState()->open_libraries(sol::lib::base, sol::lib::os, sol::lib::package);
    Lua::Get()->SetPackageRoot(p + "/Game/scripts/");
    Lua::Get()
        ->Register<GameLog>("Log")
        .set("Info", &GameLog::info)
        .set("Error", &GameLog::error)
        .set("Debug", &GameLog::debug)
        .set("Fatal", &GameLog::fatal);
    Lua::Get()->Execute("app.lua");
    Lua::Get()->RunFunction("onStart");

    GetThreadPool().Enqueue([]() {
        Lua::Get()->RunFunction("onThread");
    });

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
    ServerSocket::Get()->OnRecieve().Add(
        [](std::string msg)
        {
          if (msg.compare("scene_info") == 0)
          {
            const auto sceneName = mtEngine::Scenes::Get()->GetScene()->GetName();
            json j;
            j["scene_info"]["name"] = sceneName;
            PLOGI << j.dump();
            ServerSocket::Get()->emit(j.dump());
          }
        });
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
