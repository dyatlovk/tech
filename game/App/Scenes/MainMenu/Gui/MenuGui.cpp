#include "MenuGui.hpp"
#include "Scenes/Scenes.hpp"

namespace Game
{
  MenuGui::MenuGui() = default;

  void MenuGui::Update() {}

  void MenuGui::RenderList()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;
    auto viewport = ImGui::GetMainViewport()->Size;
   
    ImGui::Begin("##main_menu", nullptr, flags);
    auto win = ImGui::GetCurrentWindow();
    ImGui::SetWindowSize(ImVec2(200, 200));
    ImGui::SetWindowPos(win, ImVec2(viewport.x / 2 - ImGui::GetWindowSize().x / 2, viewport.y / 2 - ImGui::GetWindowSize().y / 2));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    if (ImGui::Button("Start Demo")) {
      PLOGD << "start game";
      mtEngine::Scenes::Get()->SetScene(std::make_unique<World>());
    }
    if (ImGui::Button("Exit")) {
      Engine::Get()->RequestClose();
    }
    ImGui::PopStyleColor(); // buttons
    
    ImGui::End();
  }
} // namespace Game
