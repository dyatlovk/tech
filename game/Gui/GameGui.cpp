#include "GameGui.hpp"

using namespace mtEngine;

namespace Game
{
  GameGui::GameGui() = default;

  GameGui::~GameGui() = default;

  void GameGui::Inventory()
  {
    int state = States::Get()->Current();
    if(state != GameStates::Inventory) return;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus;
    ImGui::SetNextWindowSize(ImVec2(viewport.x / 100 * 25.0f, viewport.y));
    static bool p_open = true;
    if (ImGui::Begin("Inventory", &p_open, window_flags))
    {
      auto window = ImGui::GetCurrentWindow()->Size;
      ImGui::SetWindowPos(ImVec2(viewport.x - window.x, 0.0f));
    }
    ImGui::End();
  }

  void GameGui::Info()
  {
    int state = States::Get()->Current();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
    static bool p_open = true;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x / 100 * 20.0f, viewport.y));
    if (ImGui::Begin("Left", &p_open, window_flags))
    {
      auto delta = Engine::Get()->GetDeltaRender();
      auto fps = Engine::Get()->GetFps();
      auto deltaUpdate = Engine::Get()->GetDelta();
      
      ImGui::Text("%s", GameStates::ToString(state).c_str());
      ImGui::Separator();
      ImGui::Text("Render: %f ms/f", delta.AsSeconds() * 1000);
      ImGui::Text("Updates: %f ms/f", deltaUpdate.AsSeconds()  * 1000);
      ImGui::Text("FPS: %d", fps);
      ImGui::Separator();
      ImGui::Text("%s", "Console: ~");
      ImGui::Text("%s", "UI Demo: F12");
      
      if (state == GameStates::MainMenu)
      {
        ImGui::Text("%s", "Start: Enter");
        ImGui::Text("%s", "Exit: F10");
      }
      if (state == GameStates::Player)
      {
        ImGui::Text("%s", "Inventory: I");
        ImGui::Text("%s", "Pause menu: Esc");
      }
      if (state == GameStates::Inventory)
      {
        ImGui::Text("%s", "Close: Esc, I");
      }
      if (state == GameStates::PauseMenu)
      {
        ImGui::Text("%s", "Resume: Esc");
        ImGui::Text("%s", "Main menu: F10");
    }
    ImGui::End();
    }
  }
}
