#include "Console.hpp"
#include "Graphics/Graphics.hpp"
#include "Guis/Gui.hpp"
#include "Utils/String.hpp"

namespace mtEngine
{
  Console::Console() { 
    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if(key == Key::GraveAccent && action == InputAction::Press) {
        ToggleVisible();
      }
      if(key == Key::PageDown && InputAction::Press == action) {
        down = true;
      }
      if(key == Key::PageUp && InputAction::Press == action) {
        up = true;
      } 
      
      if(InputAction::Release == action) {
        down = false;
        up = false;
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
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y / 100 * HEIGHT_PERCENT));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.9f));
    ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
    ImFont *monoFont = Gui::Get()->GetFont(std::string(FONT_MONO));
    if(!monoFont) {
      PLOGE << "Font not found";
      return;
    };
    ImGui::PushFont(monoFont);
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
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
      for (const auto &list : logList)
      {
        ImGui::Text("%s", list.c_str());
      }
      ImGui::PopStyleColor();

      KeyboardScroll(scrollDown);
      if (scrollDown)
        ImGui::SetScrollHereY(1.0f);

      scrollDown = false;
      ImGui::EndChild();
    }
    ImGui::PopStyleColor(); // end window
    ImGui::PopStyleColor(); // end scroll

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    const char *helperTitle = "##ConsoleInputHelper";
    std::string ps_1 = std::string(PS1);
    float textboxSize = ImGui::CalcTextSize(ps_1.c_str()).x + (ImGui::GetStyle().FramePadding.x);
    ImGui::SetNextItemWidth(textboxSize);
    ImGuiInputTextFlags helperFlags = ImGuiInputTextFlags_ReadOnly;
    ImGui::InputText(helperTitle, &ps_1, helperFlags);
    ImGui::SameLine(0.0f, -1.0f);
    ImGui::PopStyleColor();

    const char *title = "##ConsoleInput";
    ImGui::SetKeyboardFocusHere();
    ImGuiInputTextFlags inputFlags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    std::string command_line = "";
    if (ImGui::InputText(title, &command_line, inputFlags, &InputCallback, (void*)this))
    {
      CVars::Get()->Exec(command_line);
      AddHistory(command_line);
      scrollDown = true;
    }
    ImGui::PopStyleColor();
    ImGui::PopFont();
    ImGui::End();
  }

  void Console::KeyboardScroll(bool scrollDown)
  {
    float pos = ImGui::GetScrollY();
    float fontSize = ImGui::GetFontSize();
    if(down && pos < ImGui::GetScrollMaxY()) {
      pos += fontSize;
      ImGui::SetScrollY(pos);
      scrollDown = false;
    };
    if(up && pos > 0) {
      pos -= fontSize;
      ImGui::SetScrollY(pos);
      scrollDown = false;
    };
  }

  int Console::InputCallback(ImGuiInputTextCallbackData* data)
  {
    Console* con = (Console*)data->UserData;
    if(data->EventFlag != ImGuiInputTextFlags_CallbackHistory) return 0;

    const int prev_history_pos = con->historyPos;
    if(data->EventKey == ImGuiKey_UpArrow) {
      if (con->historyPos == -1)
        con->historyPos = con->history.size() - 1;
      else if (con->historyPos > 0)
        con->historyPos--;
    }
    
    if(data->EventKey == ImGuiKey_DownArrow) {
      if (con->historyPos != -1)
        if (++con->historyPos >= con->history.size())
          con->historyPos = -1;
    }
   
    if (prev_history_pos != con->historyPos) {
      const std::string history_str = (con->historyPos >= 0) ? con->history[con->historyPos] : "";
      data->DeleteChars(0, data->BufTextLen);
      data->InsertChars(0, history_str.c_str());
    }

    return 0;
  }
}
