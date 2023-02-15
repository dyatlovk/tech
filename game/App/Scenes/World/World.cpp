#include "World.hpp"

#include <memory>

#include <third_party/json/json.hpp>

#include "Graphics/Texture.hpp"
#include "Gui/GameGui.hpp"
#include "Gui/Notify.hpp"
#include "Guis/Gui.hpp"
#include "Scenes/Components/Transform.hpp"
#include "Scenes/EntityManager.hpp"
#include "Scenes/World/Client/Communication.hpp"
#include "Scenes/World/Events/WorldEvents.hpp"
#include "Scenes/World/Vars/Entities.hpp"

namespace Game
{
  using json = nlohmann::json;

  World::World()
      : Scene(std::make_unique<FPSCamera>())
      , m_var_entities(std::make_unique<Entities>())
      , gui(std::make_unique<WorldGui>())
      , notify(std::make_unique<Notify>())
      , m_grid(std::make_unique<Grid>())
  {
    json j;
    j["scene_info"]["name"] = std::string(NAME);
    PLOGI << j.dump();
    ServerSocket::Get()->emit(j.dump());
  }

  void World::Start()
  {
    Keyboard::Get()->OnKey().Add(
        [this](Key key, InputAction action, InputMod mods)
        {
          auto camera = mtEngine::Scenes::Get()->GetCamera();
          if (Gui::Get()->GetConsole()->IsVisible())
            return;
          if (key == Key::I && action == InputAction::Press)
          {
            show_inv = !show_inv;
            if (show_inv)
            {
              camera->SetMoveIsPaused(true);
              Mouse::Get()->ShowCursor();
            }
            if (!show_inv)
            {
              camera->SetMoveIsPaused(false);
              Mouse::Get()->HideCursor();
              Mouse::Get()->SetCenterPosition();
            }
          }
        });

    // Mouse::Get()->HideCursor();

    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    CVars::Get()->Add("scenes", "notify_add", {""}, "Add notify message", "scenes add_notify <text> <duration>",
        [this](CVarParam &args, Input &input, bool &isValid)
        {
          if (input.empty())
          {
            isValid = false;
            return;
          }
          isValid = true;

          const std::string text = input.at(0);
          float duration = Message::SHOW_TIME;
          try
          {
            duration = std::stof(input.at(1));
          }
          catch (const std::out_of_range &oor)
          {
          }

          notify->Add({text, duration});
        });

    ::World::Events::onConsoleShow();
    ::World::Events::onConsoleClose();

    GameGui::Get()->appendListener(GUI::Events::OnStatsToggle, [this]() {
      notify->Add({"stats toggled", 2000});
    });

    Engine::Get()->GetApp()->GetThreadPool().Enqueue(
        []()
        {
          const std::string p(RESOURCES);
          Texture::Create("bg_game", p + "/Game/textures/bg_game.jpg");
          Texture::Create("pistol_icon", p + "/Game/textures/weapons/pistol.png");
          Texture::Create("rifle_icon", p + "/Game/textures/weapons/rifle.png");
          Texture::Create("ammo_icon", p + "/Game/textures/weapons/ammo.png");
          Texture::Create("vss_icon", p + "/Game/textures/weapons/vss.png");
          Texture::Create("armor_icon", p + "/Game/textures/armor.png");
          Texture::Create("grenade_icon", p + "/Game/textures/weapons/grenade.png");
        });

    const std::string p(RESOURCES);
    EntityManager::CreateFromFile(p + "/Game/scenes/World.json");

    // send to client
    {
      auto _e = mtEngine::Scenes::Get()->GetStructure()->QueryAll();
      json j;
      for (const auto &e : _e)
      {
        const auto matrix = e->GetComponent<Transform>()->GetTranslation();
        j["scene_info"]["entities"][e->GetName()]["transform"]["x"] = matrix.x;
        j["scene_info"]["entities"][e->GetName()]["transform"]["y"] = matrix.y;
        j["scene_info"]["entities"][e->GetName()]["transform"]["z"] = matrix.z;
      }
      auto camera = mtEngine::Scenes::Get()->GetCamera();
      j["scene_info"]["camera"]["transform"]["x"] = camera->GetPosition().x;
      j["scene_info"]["camera"]["transform"]["y"] = camera->GetPosition().y;
      j["scene_info"]["camera"]["transform"]["z"] = camera->GetPosition().z;
      j["scene_info"]["camera"]["dir"]["x"] = camera->GetRotation().x;
      j["scene_info"]["camera"]["dir"]["y"] = camera->GetRotation().y;
      j["scene_info"]["camera"]["dir"]["z"] = camera->GetRotation().z;
      ServerSocket::Get()->emit(j.dump());
    }

    // recieve from client
    {
      ServerSocket::Get()->OnRecieve().Add(
          [](std::string msg)
          {
            const auto isValid = json::accept(msg.c_str());
            if (!isValid)
            {
              PLOGD << "json is not valid";
              return;
            }
            json j;
            const auto parsed = j.parse(msg.c_str());
            if (parsed.find("object_info") != parsed.end())
            {
              PLOGI << "client send: object_info";
              const auto recieved = Game::Client::MakeObject(&parsed);
              const auto _e = mtEngine::Scenes::Get()->GetStructure()->GetEntity(recieved->entity.name);
              if (!_e)
                return;
              const auto entity = recieved->entity;
              auto transform = _e->GetComponent<Transform>();
              transform->SetTranslation(entity.transform->translate->x, entity.transform->translate->y, entity.transform->translate->z);
              return;
            }
            if (parsed.find("scene_info") != parsed.end())
            {
              PLOGI << "client send: scene_info";
              const auto recieved = Game::Client::MakeScene(&parsed);
              for (const auto &e : recieved->entities)
              {
                const auto _e = mtEngine::Scenes::Get()->GetStructure()->GetEntity(e->name);
                auto transform = _e->GetComponent<Transform>();
                transform->SetTranslation(e->transform->translate->x, e->transform->translate->y, e->transform->translate->z);
              }
              return;
            }
          });
    }

    PLOGD << "world started";
  }

  void World::BeforeUpdate() {}

  void World::Update()
  {
    gui->PlayerInfo();
    if (show_inv)
      gui->Inventory();
    notify->Render();
    m_grid->Update();
  }

  void World::AfterUpdate() {}

  void World::Shutdown()
  {
    CVars::Get()->RemoveName("scenes", "notify_add");
    Gui::Get()->GetConsole()->OnClose().RemoveObservers();
    Gui::Get()->GetConsole()->OnShow().RemoveObservers();
    gui = nullptr;
    notify = nullptr;
    m_grid = nullptr;
    m_var_entities = nullptr;
    PLOGD << "world shutdown";
  }
} // namespace Game
