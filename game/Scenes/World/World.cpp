#include "World.hpp"

#include "Devices/Window.hpp"
#include "Engine/Engine.hpp"
#include "Gui/Notify.hpp"
#include "Guis/Gui.hpp"
#include "Graphics/Texture.hpp"
#include "Resources/ResourcesManager.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start()
  {
    gui = std::make_unique<WorldGui>();
    notify = std::make_unique<Notify>();
    Keyboard::Get()->OnKey().Add([this](Key key, InputAction action, InputMod mods) {
      if(Gui::Get()->GetConsole()->IsVisible()) return;
      if(key == Key::I && action == InputAction::Press) {
        show_inv = !show_inv;
      }
    });

    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    CVars::Get()->Add("scenes", "notify_add", {""}, "Add notify message", "scenes add_notify <text> <duration>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.empty()) {
        isValid = false;
        return;
      }
      isValid = true;

      const std::string text = input.at(0);
      float duration = Message::SHOW_TIME;
      try {
        duration = std::stof(input.at(1));
      } catch (const std::out_of_range& oor) {}

      notify->Add({text, duration});
    });

    Engine::Get()->GetApp()->GetThreadPool().Enqueue([]() {
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
    auto shader = Shader::CreateDefault();
    auto mesh = Mesh::Create("mesh", p + "/Game/models/boxes.gltf");
    Model::Create("model", shader.get(), mesh.get(), nullptr);
    PLOGD << "world started";
  }

  void World::BeforeUpdate() {
  }

  void World::Update()
  {
    gui->PlayerInfo();
    if(show_inv) gui->Inventory();
    notify->Render();

    auto model = ResourcesManager::Get()->find<Model>("model");
    if(model) model->Draw();
  }

  void World::AfterUpdate() {

  }

  void World::Shutdown()
  {
    CVars::Get()->RemoveName("scenes", "notify_add");
    gui = nullptr;
    notify = nullptr;
    PLOGD << "world shutdown";
  }
} // namespace Game
