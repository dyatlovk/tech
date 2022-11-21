#include "World.hpp"

#include <memory>

#include "Devices/Window.hpp"
#include "Graphics/Texture.hpp"
#include "Gui/Notify.hpp"
#include "Guis/Gui.hpp"
#include "Scenes/Components/Transform.hpp"
#include "third_party/glm/ext/matrix_float4x4.hpp"
#include "Scenes/Scenes.hpp"

namespace Game
{
  World::World()
      : Scene(std::make_unique<FPSCamera>())
  {
  }

  void World::Start()
  {
    gui = std::make_unique<WorldGui>();
    notify = std::make_unique<Notify>();
    m_grid = std::make_unique<Grid>();
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

    Gui::Get()->GetConsole()->OnShow().Add(
        []()
        {
          Mouse::Get()->ShowCursor();
          auto camera = mtEngine::Scenes::Get()->GetCamera();
          if (camera)
            camera->SetMoveIsPaused(true);
        });

    Gui::Get()->GetConsole()->OnClose().Add(
        []()
        {
          Mouse::Get()->HideCursor();
          auto camera = mtEngine::Scenes::Get()->GetCamera();
          if (camera)
            camera->SetMoveIsPaused(false);
          Mouse::Get()->SetCenterPosition();
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
    auto boxes = mtEngine::Scenes::Get()->GetStructure()->CreateEntity();
    boxes->AddComponent<Model>(Model::Create(p + "/Game/models/boxes.gltf"));
    boxes->AddComponent<Transform>(glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    auto yard = mtEngine::Scenes::Get()->GetStructure()->CreateEntity();
    yard->AddComponent<Model>(Model::Create(p + "/Game/models/yard/yard.gltf"));
    yard->AddComponent<Transform>(glm::vec3(0.0, -1.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    glEnable(GL_DEPTH_TEST);

    PLOGD << "world started";
  }

  void World::BeforeUpdate() {

  }

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
    PLOGD << "world shutdown";
  }
} // namespace Game
