#include "GameGui.hpp"
#include "Engine/Events.hpp"
#include "Scenes/Scenes.hpp"

using namespace mtEngine;

namespace Game
{
  GameGui *GameGui::Instance = nullptr;

  GameGui::GameGui()
  {
    Instance = this;
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    Events::Get()->GetCallBackList()->append([this](){process();});
    CVars::Get()->Add("app", "stats", {"1"}, "Show stats", "app stats <1|0>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.empty()) {
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
      OnStatsToggleCallback();
    });

    CVars::Get()->Add("app", "ui_debug", {"0"}, "Show windows rectangles", "app ui_debug <1|0>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.empty()) {
        isValid = false;
        return;
      }
      if(input.at(0) != "1" && input.at(0) != "0") {
        isValid = false;
        return;
      }
      isValid = true;

      int flag = std::stoi(input.at(0));

      if(flag == 0) {
        showUIDebug = false;
      }

      if(flag == 1) {
        showUIDebug = true;
      }
    });
  };

  GameGui::~GameGui() = default;

  auto GameGui::Init() -> std::unique_ptr<GameGui>
  {
    auto s = std::make_unique<GameGui>();

    return s;
  }

  void GameGui::Update() {
  }

  void GameGui::Debug()
  {
    if(!showUIDebug) return;
    ImGuiContext& g = *GImGui;
    ImGuiIO& io = g.IO;
    ImGuiMetricsConfig* cfg = &g.DebugMetricsConfig;
    for (int n = 0; n < g.Windows.Size; n++)
    {
      ImGuiWindow* window = g.Windows[n];
      if (!window->WasActive)
        continue;
      ImDrawList* draw_list = ImGui::GetForegroundDrawList(window);
      ImRect r = window->Rect();
      draw_list->AddRect(r.Min, r.Max, IM_COL32(255, 0, 128, 255));
    }
  }

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
    if (ImGui::Begin("Stats", &p_open, window_flags))
    {
      auto delta = Engine::Get()->GetDeltaRender();
      auto fps = Engine::Get()->GetFps();
      auto deltaUpdate = Engine::Get()->GetDelta();
      auto camera = mtEngine::Scenes::Get()->GetCamera();

      ImGui::Text("%s", "Console: ~");
      ImGui::Text("%s", "UI Demo: F12");
      ImGui::Separator();
      ImGui::Text("Render: %f ms/f", delta.AsSeconds() * 1000);
      ImGui::Text("Updates: %f ms/f", deltaUpdate.AsSeconds()  * 1000);
      ImGui::Text("FPS: %d", fps);
      ImGui::Separator();
      if(camera) {
        ImGui::Text("Camera");
        ImGui::Separator();
        ImGui::Text("Pos x: %f", camera->GetPosition().x);
        ImGui::Text("Pos y: %f", camera->GetPosition().y);
        ImGui::Text("Pos z: %f", camera->GetPosition().z);
        ImGui::Text("Dir x: %f", camera->GetRotation().x);
        ImGui::Text("Dir y: %f", camera->GetRotation().y);
        ImGui::Text("Dir z: %f", camera->GetRotation().z);
      }
    }
    ImGui::PopFont();
    ImGui::End();
  }

  auto GameGui::OnStatsToggleCallback() -> void
  {
    enqueue(GUI::Events::OnStatsToggle);
    LuaBind::Get()->RunFunction("onStatsToggle");
  }
}
