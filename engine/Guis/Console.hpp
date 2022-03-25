#pragma once

#include "Inputs/Input.hpp"

#include "Imgui.hpp"

namespace mtEngine {
  class Console
  {
    using History = std::vector<std::string>;
    public:
      static constexpr float HEIGHT_PERCENT = 45.0f;
      static constexpr std::string_view PS1 = ">>";
      
      Console();

      void Start();
      void Render();
      void Update();

      bool ToggleVisible() { visible = !visible; return visible; };
      bool IsVisible() { return visible; };

      void AddHistory(const std::string &command) {
        history.push_back(command);
      }

      History *GetHistory() const
      {
        return const_cast<History *>(&history);
      }

      void ShutDown()
      {
        history.clear();
      }

    private:
      bool visible = false;
      bool down = false;
      bool up = false;
      int historyPos = -1;

      void KeyboardScroll(bool scrollDown = false);
      static int InputCallback(ImGuiInputTextCallbackData* data);

      History history;
  };
}
