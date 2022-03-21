#include "Console.hpp"

namespace mtEngine
{
  Console::Console() { 
    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if(action != InputAction::Press) return; 
      if(key == Key::GraveAccent) {
        ToggleVisible();
      }
    });
    PLOGD << "console started"; 
  };

  void Console::Start()
  {
  }

  void Console::Render()
  {
    if (!visible) return;
    float height = 45.0f;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y / 100 * height));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.9f));
    static bool scrollDown;
    if (ImGui::Begin("Console", &visible, window_flags))
    {
      const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
      ImGui::BeginChild("ConsoleContent", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
      if (ImGui::BeginPopupContextWindow())
      {
        ImGui::EndPopup();
      }

      auto logList = Log::Get()->GetMomory();
      for (const auto &list : logList)
      {
        ImGui::Text("%s", list.c_str());
      }
      if (scrollDown)
        ImGui::SetScrollHereY(1.0f);
      scrollDown = false;
      ImGui::EndChild();
    }
    ImGui::PopStyleColor();

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    const char *helperTitle = "##ConsoleInputHelper";
    std::string helperText = ">>";
    float textboxSize = ImGui::CalcTextSize(helperText.c_str()).x + (ImGui::GetStyle().FramePadding.x);
    ImGui::SetNextItemWidth(textboxSize);
    ImGuiInputTextFlags helperFlags = ImGuiInputTextFlags_ReadOnly;
    ImGui::InputText(helperTitle, &helperText, helperFlags);
    ImGui::SameLine(0.0f, -1.0f);
    ImGui::PopStyleColor();

    std::string command = "";
    const char *title = "##ConsoleInput";
    ImGui::SetKeyboardFocusHere();
    ImGuiInputTextFlags inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText(title, &command, inputFlags))
    {
      //TODO: command exec
      CVars::Get()->Exec(command);
      scrollDown = true;
    }
    ImGui::PopStyleColor();
    ImGui::End();
  }
}
