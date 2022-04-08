#include "World.hpp"

#include "Guis/Gui.hpp"
#include "Graphics/Texture.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start()
  {
    gui = std::make_unique<WorldGui>();
    layout = std::make_unique<WorldLayout>();
    Keyboard::Get()->OnKey().Add([this](Key key, InputAction action, InputMod mods) {
      if(key == Key::I && action == InputAction::Press) {
        show_inv = !show_inv;
      }
    });

    const std::string p(RESOURCES);
    Texture::Create("bg", p + "/Game/textures/bg.jpg");
    Texture::Create("pistol_icon", p + "/Game/textures/weapons/pistol.png");
    Texture::Create("rifle_icon", p + "/Game/textures/weapons/rifle.png");
    Texture::Create("ammo_icon", p + "/Game/textures/weapons/ammo.png");
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
    auto bgImage = ResourcesManager::Get()->find<Texture>("bg");
    ImGui::Image((void*)(intptr_t)bgImage->GetTexture(), viewport);
    ImGui::PopStyleVar();
    ImGui::End();
  }

  void World::Update()
  {
    gui->PlayerInfoDock();
    if(show_inv) gui->Inventory();
  }

  void World::AfterUpdate() {}

  void World::Shutdown()
  {
    gui = nullptr;
    layout = nullptr;
  }
} // namespace Game
