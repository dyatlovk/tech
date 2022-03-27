#include "GameGui.hpp"

using namespace mtEngine;

namespace Game
{
  GameGui::GameGui() = default;

  void GameGui::Update() { }

  void GameGui::Inventory()
  {
    int state = States::Get()->Current();
    if(state != GameStates::Inventory) return;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
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

  void GameGui::Help(bool open)
  {
    if(!open) return;
    int state = States::Get()->Current();

    std::string msg = GameStates::ToString(state);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMouseInputs;
    auto viewport = ImGui::GetMainViewport()->Size;
    
    auto font_size = ImGui::CalcTextSize(msg.c_str());
    
    ImVec4 green = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, green);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 2.0f);
    
    ImGui::Begin("##Help", &open, window_flags);
    auto win = ImGui::GetCurrentWindow();
    ImGui::SetWindowSize(ImVec2(font_size.x + 50, font_size.y + 50));
    ImGui::SetWindowPos(win, ImVec2(viewport.x / 2 - ImGui::GetWindowSize().x / 2, viewport.y / 2 - ImGui::GetWindowSize().y / 2));
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - (font_size.x / 2), ImGui::GetWindowSize().y / 2 - (font_size.y / 2)));
    ImGui::Text("%s", msg.c_str());

    ImGui::PopStyleColor(); // window bg
    ImGui::PopStyleColor(); // border col
    ImGui::PopStyleVar(); // border size
    ImGui::End();
  }
}
