#include "WorldGui.hpp"

#include "../../MainMenu/MainMenu.hpp"
#include "Devices/Keyboard.hpp"
#include "Guis/Gui.hpp"
#include "../../../Gui/Math.hpp"

namespace Game
{
  WorldGui::WorldGui() = default;

  void WorldGui::PlayerInfoDock()
  {
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

  void WorldGui::Inventory()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus;
   
    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0.17f, 0.17f, 0.17f, 1.0f});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {20.0f, 20.0f});
   
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    float width = 37 * vSize.x / 100;
    float height = vSize.y;
    ImGui::SetNextWindowPos({vSize.x - width, 0}, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize({width, height});
    ImGui::Begin("##Inventory", nullptr, flags);
    CharacterItem();
    Weapons();
    Items();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
    ImGui::End();
  }

  void WorldGui::CharacterItem()
  {
    static ImVec4 colf = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
    const ImU32 col = ImColor(colf);
    
    ImDrawList *draw = ImGui::GetWindowDrawList();
    auto win_size = ImGui::GetCurrentWindow()->WorkRect;
    float heightItem = 80;
    int size = 4;
    float w = Game::divide_rectangle(size, padding, win_size.GetWidth());
    
    panelCursor = ImGui::GetCursorScreenPos();
    ImVec2 p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + w, p.y + heightItem), col);
    const char *firstText = "12 Strength";
    ImVec2 firstTextSize = ImGui::CalcTextSize(firstText);
    ImGui::SetCursorScreenPos({p.x + w / 2 - firstTextSize.x / 2, p.y + heightItem / 2 - firstTextSize.y / 2});
    ImGui::Text("%s", firstText);
    
    ImGui::SetCursorScreenPos({p.x + w + padding, p.y});
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + w, p.y + heightItem), col);
    const char *secondText = "8 Dexterity";
    ImVec2 secondTextSize = ImGui::CalcTextSize(secondText);
    ImGui::SetCursorScreenPos({p.x + w / 2 - secondTextSize.x / 2, p.y + heightItem / 2 - secondTextSize.y / 2});
    ImGui::Text("%s", secondText);
    
    ImGui::SetCursorScreenPos({p.x + w + padding, p.y});
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + w, p.y + heightItem), col);
    const char *threeText = "6 Intellect";
    ImVec2 threeTextSize = ImGui::CalcTextSize(threeText);
    ImGui::SetCursorScreenPos({p.x + w / 2 - threeTextSize.x / 2, p.y + heightItem / 2 - threeTextSize.y / 2});
    ImGui::Text("%s", threeText);
    
    ImGui::SetCursorScreenPos({p.x + w + padding, p.y});
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + w, p.y + heightItem), col);
    const char *fourthText = "20 Health";
    ImVec2 fouthTextSize = ImGui::CalcTextSize(fourthText);
    ImGui::SetCursorScreenPos({p.x + w / 2 - fouthTextSize.x / 2, p.y + heightItem / 2 - fouthTextSize.y / 2});
    ImGui::Text("%s", fourthText);
    
    ImGui::SetCursorScreenPos({panelCursor.x, panelCursor.y + heightItem + padding});
  }

  void WorldGui::Weapons()
  {
    static ImVec4 bgf = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
    const ImU32 bg = ImColor(bgf);
    
    ImDrawList *draw = ImGui::GetWindowDrawList();
    auto win_size = ImGui::GetCurrentWindow()->WorkRect;
   
    float width = win_size.GetWidth();
    float height = 160;
    ImVec2 p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), bg);
    
    ImGui::SetCursorScreenPos({p.x + padding, p.y + padding});
    float widthWeaponsItems = Game::divide_rectangle(2, padding, win_size.GetWidth() - 20);
    float heightWeaponsItems = 140;
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + widthWeaponsItems, p.y + heightWeaponsItems), ImColor(ImVec4(0.23f, 0.23f, 0.23f, 0.22f)));
    
    ImGui::SetCursorScreenPos({p.x + widthWeaponsItems + padding, p.y});
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + widthWeaponsItems, p.y + heightWeaponsItems), ImColor(ImVec4(0.23f, 0.23f, 0.23f, 0.22f)));
    
    ImGui::SetCursorScreenPos({panelCursor.x, p.y + height});
  }

  void WorldGui::Items()
  {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList *draw = ImGui::GetWindowDrawList();
    auto win_size = ImGui::GetCurrentWindow()->WorkRect;
    float width = win_size.GetWidth();
    float height = win_size.GetHeight() - p.y + 20.0f;
    
    draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImColor(ImVec4(0.12f, 0.12f, 0.12f, 1.0f)));
  }
} // namespace Game
