#include "WorldGui.hpp"

#include "../../MainMenu/MainMenu.hpp"
#include "Devices/Keyboard.hpp"
#include "Guis/Gui.hpp"

namespace Game
{
  WorldGui::WorldGui() = default;

  void WorldGui::PlayerInfoDock()
  {
    ImGuiWindowClass window_class2;
    window_class2.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
    window_class2.DockingAllowUnclassed = false;

    ImGui::SetNextWindowClass(&window_class2);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
    
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(vSize, ImGuiCond_Always, ImVec2(1.0f, 1.0f));
    ImGui::SetNextWindowSize({vSize.x, 70});
    
    ImGui::Begin("##player_info", nullptr, flags);
    Row();
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void WorldGui::Row()
  {
    auto dock = ImGui::GetCurrentWindow();
    ImVec2 button_sz(dock->Size.y, dock->Size.y);
    ImGui::PushStyleColor(ImGuiCol_Button, {0,0,0,0});
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, {0,0,0,0});
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0,0,0,0});
    ImGui::Button("HL: 95%", button_sz);
    ImGui::SameLine(0.0f, 1.0f);
    ImGui::Button("AR: 100%", button_sz);
    ImGui::SameLine(0.0f, 1.0f);
    ImGui::Button("ED: 40%", button_sz);
    ImGui::SameLine(0.0f, 1.0f);
    ImGui::PopStyleColor(3);
  }
} // namespace Game
