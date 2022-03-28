#include "GameGui.hpp"

using namespace mtEngine;

namespace Game
{
  GameGui::GameGui()
  {
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    CVars::Get()->Add("app", "stats", {"1"}, "Show stats", "app stats <1|0>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.size() == 0) {
        isValid = false;
        return;
      }
      if(input.at(0) != "1" && input.at(0) != "0") {
        isValid = false;
        return;
      }
      isValid = true;
      
      int flag = std::stoi(input.at(0));

      if(flag == 1) {
        showStats = true;
      }
      
      if(flag == 0) {
        showStats = false;
      }
    });
  };

  void GameGui::Update() { }

  void GameGui::Stats()
  {
    if(!showStats) return;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
    static bool p_open = true;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x / 100 * 20.0f, viewport.y));
    ImFont *monoFont = Gui::Get()->GetFont(std::string(FONT_MONO));
    ImGui::PushFont(monoFont);
    if (ImGui::Begin("Left", &p_open, window_flags))
    {
      auto delta = Engine::Get()->GetDeltaRender();
      auto fps = Engine::Get()->GetFps();
      auto deltaUpdate = Engine::Get()->GetDelta();
      
      ImGui::Text("%s", "Console: ~");
      ImGui::Text("%s", "UI Demo: F12");
      ImGui::Separator();
      ImGui::Text("Render: %f ms/f", delta.AsSeconds() * 1000);
      ImGui::Text("Updates: %f ms/f", deltaUpdate.AsSeconds()  * 1000);
      ImGui::Text("FPS: %d", fps);
    }
    ImGui::PopFont();
    ImGui::End();
  }
}
