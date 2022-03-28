#include "MainMenu.hpp"

namespace Game
{
  MainMenu::MainMenu() = default;

  MainMenu::~MainMenu() = default;

  void MainMenu::Start() {
    gui = std::make_unique<MenuGui>();
    bg_texture = std::make_unique<Texture>();
    const std::string p(RESOURCES);
    bool ret = bg_texture->LoadTextureFromFile(p + "/Game/textures/bg.jpg", &bg_image, &tex_width, &tex_height);
  }

  void MainMenu::BeforeUpdate() {}

  void MainMenu::Update() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoBringToFrontOnFocus;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });
    ImGui::Begin("MainMenu_bg", nullptr, window_flags);
    ImGui::Image((void*)(intptr_t)bg_image, ImVec2(tex_width, tex_height));
    ImGui::PopStyleVar();
    ImGui::End();
    
    gui->RenderList();
  }

  void MainMenu::AfterUpdate() {}

  void MainMenu::Shutdown() {
    gui = nullptr;
  }

} // namespace Game
