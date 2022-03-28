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
    ImGui::Begin("##main_menu", nullptr, flags);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    if (ImGui::Button("Start Demo")) {
      PLOGD << "start game";
      Scenes::Get()->SetScene(std::make_unique<World>());
    }
    if (ImGui::Button("Exit")) {
      Engine::Get()->RequestClose();
    }
    ImGui::PopStyleColor(); // buttons
    ImGui::End();
  }
} // namespace Game
