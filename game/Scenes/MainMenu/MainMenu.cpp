#include "MainMenu.hpp"

namespace Game
{
  MainMenu::MainMenu() = default;

  MainMenu::~MainMenu() = default;

  void MainMenu::Start() {
    gui = std::make_unique<MenuGui>();
    const std::string p(RESOURCES);
    auto texture = Texture::Create("bg", p + "/Game/textures/bg.jpg");
    PLOGD << "main menu started";
  }

  void MainMenu::BeforeUpdate() {}

  void MainMenu::Update() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
    window_flags |= ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });
    ImGui::Begin("MainMenu_bg", nullptr, window_flags);
    auto bgImage = ResourcesManager::Get()->find<Texture>("bg");
    ImGui::Image((void*)(intptr_t)bgImage->GetTexture(), viewport);
    ImGui::PopStyleVar();
    ImGui::End();
    
    gui->RenderList();
  }

  void MainMenu::AfterUpdate() {
  }

  void MainMenu::Shutdown() {
    gui = nullptr;
    PLOGD << "main menu shutdown";
  }

} // namespace Game
