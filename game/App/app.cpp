#include "app.hpp"
#include <unistd.h>

#include "Guis/Font.hpp"
#include "Guis/IconsFontAwesome6.h"
#include "Inputs/Input.hpp"
#include "Render/GameRender.hpp"
#include "Scripts/GameLog.hpp"
#include "Scripts/Lua/LuaBind.hpp"

namespace Game
{
  using namespace mtEngine;
  using json = nlohmann::json;
  GameApp::GameApp()
      : App("Game")
      , scene(nullptr)
      , gameGui(GameGui::Init())
      , commands(std::make_unique<AppCommands>())
  {
  }

  GameApp::~GameApp()
  {
    Graphics::Get()->SetRenderer(nullptr);
    mtEngine::Scenes::Get()->SetScene(nullptr);
    commands = nullptr;
  }

  void GameApp::Start()
  {
    std::string p(RESOURCES);

    {
      LuaBind::Get()->GetState()->open_libraries(sol::lib::base, sol::lib::package, sol::lib::os);
      LuaBind::Get()->SetPackageRoot(p + "/Game/scripts/");
      auto GameLogRegistrar = LuaBind::Get()->Register<GameLog>("Log");
      GameLogRegistrar.set("Info", &GameLog::info);
      GameLogRegistrar.set("Error", &GameLog::error);
      GameLogRegistrar.set("Debug", &GameLog::debug);
      GameLogRegistrar.set("Fatal", &GameLog::fatal);
      LuaBind::Get()->Execute("app.lua");
      LuaBind::Get()->RunFunction("onGameStart");
    }

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
    GameGui::Get()->appendListener(GUI::Events::OnStatsToggle, [](){
      PLOGI << "app subscribed";
    });
  }

  void GameApp::BeforeUpdate() {}

  void GameApp::Update()
  {
  }

  void GameApp::AfterUpdate()
  {
    GameGui::Get()->Stats();
    GameGui::Get()->Debug();
  }
} // namespace Game
