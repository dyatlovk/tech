#include "World.hpp"

#include "Gui/Notify.hpp"
#include "Guis/Gui.hpp"
#include "Graphics/Texture.hpp"

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

    std::future task = Engine::Get()->GetApp()->GetThreadPool().Enqueue([]() {
      const std::string p(RESOURCES);
      Texture::Create("bg_game", p + "/Game/textures/bg_game.jpg");
      Texture::Create("pistol_icon", p + "/Game/textures/weapons/pistol.png");
      Texture::Create("rifle_icon", p + "/Game/textures/weapons/rifle.png");
      Texture::Create("ammo_icon", p + "/Game/textures/weapons/ammo.png");
      Texture::Create("vss_icon", p + "/Game/textures/weapons/vss.png");
      Texture::Create("armor_icon", p + "/Game/textures/armor.png");
      Texture::Create("grenade_icon", p + "/Game/textures/weapons/grenade.png");
    });


    PLOGD << "world started";
  }

  void World::BeforeUpdate() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
    window_flags |= ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });
    ImGui::Begin("bg", nullptr, window_flags);
    auto bgImage = ResourcesManager::Get()->find<Texture>("bg_game");
    if(bgImage) {
        auto tex = bgImage->GetTexture();
        ImGui::Image((void*)(intptr_t)tex, viewport);
    }
    ImGui::PopStyleVar();
    ImGui::End();
  }

  void World::Update()
  {
    gui->PlayerInfo();
    if(show_inv) gui->Inventory();
    notify->Render();
  }

  void World::AfterUpdate() {}

  void World::Shutdown()
  {
    CVars::Get()->RemoveName("scenes", "notify_add");
    gui = nullptr;
    notify = nullptr;
    PLOGD << "world shutdown";
  }
} // namespace Game
