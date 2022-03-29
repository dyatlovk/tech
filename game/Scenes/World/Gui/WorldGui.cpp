#include "WorldGui.hpp"

#include "../../MainMenu/MainMenu.hpp"
#include "Devices/Keyboard.hpp"
#include "Guis/Gui.hpp"

namespace Game
{
  WorldGui::WorldGui() = default;

  void WorldGui::Window()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoDocking;
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
  }

  void WorldGui::PlayerInfoDock()
  {
    ImGuiWindowClass window_class2;
    window_class2.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResize;
    window_class2.DockingAllowUnclassed = false;

    ImGui::SetNextWindowClass(&window_class2);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0.0f, 0.0f});
    ImGui::Begin("##player_info", nullptr, flags);
    Items();
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void WorldGui::Items()
  {
    auto info = ImGui::GetCurrentWindow();
    ImGui::BeginChild("Item", {info->Size.y, 0}, false);
    ImGui::Text("Item1");
    ImGui::EndChild();
    
    ImGui::SameLine(0.0f, 0.0f);
    
    ImGui::BeginChild("Item2", {info->Size.y, 0}, false);
    ImGui::Text("Item2");
    ImGui::EndChild();
    
    ImGui::SameLine(0.0f, 0.0f);
  
    ImGui::BeginChild("Item3", {info->Size.y, 0}, false);
    ImGui::Text("Item3");
    ImGui::EndChild();
  }
} // namespace Game
