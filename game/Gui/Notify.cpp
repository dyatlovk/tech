#include "Notify.hpp"
#include "Engine/CVars.hpp"
#include "third_party/imgui/imgui.h"

namespace Game
{
  Notify::Notify()
      : startPos({20, 100}){};

  void Notify::Remove(int index)
  {
    notifications.erase(notifications.begin() + index);
  }

  void Notify::Render() {
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {20.0f, 20.0f});
    ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize({400, vSize.y - 80 - 20});
    ImGui::Begin("##notify", nullptr, flags);
    RenderMessages();
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void Notify::RenderMessages()
  {
    float messageWidth = 400;
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    auto dock = ImGui::GetCurrentWindow();  
    ImVec2 dockSize = dock->WorkRect.GetSize();
    auto window = ImGui::GetCurrentWindow();
    const ImU32 bg = ImColor( ImVec4(0.17f, 0.17f, 0.17f, 0.9f));
    ImGui::SetCursorScreenPos({startPos.x, dockSize.y + 20});
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImDrawList *draw = ImGui::GetWindowDrawList();
    // debug cursor
    // draw->AddRectFilled(pos, {pos.x + 5, pos.y - 5}, IM_COL32(0, 255, 0, 255));

    for (auto i = 0; i < notifications.size(); i++)
    {
      auto *msg = &notifications[i];

      if (msg->isExpired())
      { 
        Remove(i);
        continue;
      }

      ImVec2 padding = {20, 20};
      float margin = 10;
      float wrapWidth = ImGui::GetCursorPos().x + messageWidth - padding.x * 2;
      ImGui::PushTextWrapPos(wrapWidth);
      std::string content = *msg->GetContent();
      ImVec2 contentSize = ImGui::CalcTextSize(content.c_str(), nullptr, false, wrapWidth);
      ImVec2 notifyPos = ImGui::GetCursorScreenPos();
      ImVec2 rectUpperLeft = {notifyPos.x, notifyPos.y - contentSize.y - padding.y * 2};
      ImVec2 rectLowerRight = {notifyPos.x + messageWidth, notifyPos.y};
      draw->AddRectFilled(rectUpperLeft, rectLowerRight, bg);
      ImGui::SetCursorScreenPos({notifyPos.x + 20, notifyPos.y - contentSize.y - padding.y});
      ImGui::Text("%s", content.c_str());
      ImGui::PopTextWrapPos();

      // set next pos
      ImGui::SetCursorScreenPos({rectUpperLeft.x, rectUpperLeft.y - margin});
    }
  }
} // namespace Game
