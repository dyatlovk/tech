#include "WorldGui.hpp"

#include "../../MainMenu/MainMenu.hpp"
#include "Devices/Keyboard.hpp"

namespace Game
{
  WorldGui::WorldGui() = default;

  void WorldGui::Window()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    
    ImGui::Begin("##world_window", nullptr, flags);
    auto win = ImGui::GetCurrentWindow();
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    if (ImGui::Button("MainMenu"))
    {
      Scenes::Get()->SetScene(std::make_unique<MainMenu>());
    }
    ImGui::PopStyleColor(); // buttons
    ImGui::End();
    
    if(Keyboard::Get()->GetKey(Key::Escape) == InputAction::Press) {
    }
  }
} // namespace Game
