#include "WorldGui.hpp"

#include "Guis/Font.hpp"
#include "../../MainMenu/MainMenu.hpp"
#include "Devices/Keyboard.hpp"
#include "Guis/Gui.hpp"
#include "../../../Gui/Math.hpp"
#include "Guis/IconsFontAwesome6.h"

namespace Game
{
  WorldGui::WorldGui() { }

  void WorldGui::PlayerInfoDock()
  {
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {20.0f, 0.0f});
    
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos({vSize.x, vSize.y - 20}, ImGuiCond_Always, ImVec2(1.0f, 1.0f));
    ImGui::SetNextWindowSize({vSize.x, 80});
    
    ImGui::Begin("##player_info", nullptr, flags);
    RowLeft();
    RowRight();
    ImGui::End();
    ImGui::PopStyleVar();
  }

  void WorldGui::RowLeft()
  {
    ImFont *iconFont = ResourcesManager::Get()->find<Font>("icons")->GetFont();
    ImFont *boldFont = ResourcesManager::Get()->find<Font>("ui_bold")->GetFont();
    if(!iconFont || !boldFont) return;
    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    float pad = 5;
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.2));
    auto dock = ImGui::GetCurrentWindow();
    ImVec2 dockSize = dock->WorkRect.GetSize();
    ImDrawList *draw = ImGui::GetWindowDrawList();
    ImVec2 itemSize = {dock->Size.y, dock->Size.y};
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImVec2 hudCursor = ImGui::GetCursorScreenPos();
   
    draw->AddRectFilled(p, ImVec2(p.x + itemSize.x, p.y + itemSize.y), bg);
    const char *HealthText = "100";
    const char *HealthIcon = ICON_FA_HEART_PULSE;
    ImVec2 HealthTextSize = ImGui::CalcTextSize(HealthText);
    ImVec2 HealthIconSize = ImGui::CalcTextSize(HealthIcon);
    ImVec2 HealthBound = {HealthTextSize.x + HealthIconSize.y, HealthIconSize.y + 15.0f + HealthTextSize.y};
   
    // Health
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - HealthIconSize.x / 2 - 6, p.y + itemSize.y / 2 - HealthIconSize.y - 5});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", HealthIcon);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - HealthTextSize.x / 2, p.y + itemSize.y / 2 - HealthTextSize.y / 2 + 15});
    ImGui::PushFont(boldFont);
    ImGui::TextColored(textColor, "%s", HealthText);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({p.x + itemSize.x + pad, p.y});
   
    // Armor
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + itemSize.x, p.y + itemSize.y), bg);
    const char *armorText = "87";
    const char *armorIconText = ICON_FA_USER_SHIELD;
    ImVec2 armorTextSize = ImGui::CalcTextSize(armorText);
    ImVec2 armorIconSize = ImGui::CalcTextSize(armorIconText);
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - armorIconSize.x / 2 - 5, p.y + itemSize.y / 2 - armorIconSize.y - 5});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", armorIconText);
    ImGui::PopFont();
    ImGui::PushFont(boldFont);
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - armorTextSize.x / 2, p.y + itemSize.y / 2 - armorTextSize.y + 23});
    ImGui::TextColored(textColor, "%s", armorText);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({p.x + itemSize.x + pad, p.y});
   
    // power
    p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + itemSize.x, p.y + itemSize.y), bg);
    const char *powerText = "99";
    const char *powerIconText = ICON_FA_PERSON_RUNNING;
    ImVec2 powerTextSize = ImGui::CalcTextSize(powerText);
    ImVec2 powerIconSize = ImGui::CalcTextSize(powerIconText);
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - powerIconSize.x / 2 - 5, p.y + itemSize.y / 2 - powerIconSize.y - 3});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", powerIconText);
    ImGui::PopFont();
    ImGui::PushFont(boldFont);
    ImGui::SetCursorScreenPos({p.x + itemSize.x / 2 - powerTextSize.x / 2, p.y + itemSize.y / 2 - powerTextSize.y + 23});
    ImGui::TextColored(textColor, "%s", powerText);
    ImGui::PopFont();

    // to right pos
    ImGui::SetCursorScreenPos({hudCursor.x + dockSize.x, p.y});
  }

  void WorldGui::RowRight()
  {
    float pad = 5;
    float padBig = 10;
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.2f));
    auto dock = ImGui::GetCurrentWindow();
    ImDrawList *draw = ImGui::GetWindowDrawList();
    ImVec2 dockSize = dock->WorkRect.GetSize();
    ImVec2 itemSize = {dockSize.y, dockSize.y};
    ImVec2 doubleItemSize = {itemSize.x * 2, itemSize.y};
    ImFont *boldFont = ResourcesManager::Get()->find<Font>("ui_bold")->GetFont();
    ImVec2 dockPos = ImGui::GetCursorScreenPos(); // cursor on max right
   
    // primary weapon
    ImGui::SetCursorScreenPos({dockPos.x - doubleItemSize.x, dockPos.y});
    ImVec2 primaryCursor = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(primaryCursor, ImVec2(primaryCursor.x + (doubleItemSize.x), primaryCursor.y + doubleItemSize.y), bg);
    auto primaryImg = ResourcesManager::Get()->find<Texture>("rifle_icon");
    ImVec2 primaryImgSize = {(float)primaryImg->GetWidth(), (float)primaryImg->GetHeight()};
    ImGui::SetCursorScreenPos({primaryCursor.x + (doubleItemSize.x / 2 - primaryImgSize.x / 2), primaryCursor.y + (doubleItemSize.y / 2 - primaryImgSize.y / 2)});
    ImGui::Image((void*)(intptr_t)primaryImg->GetTexture(), primaryImgSize);

    //primary ammo
    ImGui::SetCursorScreenPos({primaryCursor.x - pad - itemSize.x, primaryCursor.y});
    ImVec2 primaryAmmoCursor = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(primaryAmmoCursor, ImVec2(primaryAmmoCursor.x + itemSize.x, primaryAmmoCursor.y + itemSize.y), bg);
    const char *primAmmoText = "1340";
    ImVec2 primAmmoSize = ImGui::CalcTextSize(primAmmoText);
    ImGui::SetCursorScreenPos({primaryAmmoCursor.x + (itemSize.x / 2 - primAmmoSize.x / 2), primaryAmmoCursor.y + 15});
    ImGui::Text("%s", primAmmoText);
    auto primaryAmmoImg = ResourcesManager::Get()->find<Texture>("ammo_icon");
    ImVec2 primaryAmmoImgSize = {(float)primaryAmmoImg->GetWidth(), (float)primaryAmmoImg->GetHeight()};
    ImGui::SetCursorScreenPos({primaryAmmoCursor.x + (itemSize.x / 2 - primaryAmmoImgSize.x / 2), primaryAmmoCursor.y + (itemSize.y / 2 - primaryAmmoImgSize.y / 2) + 15});
    ImGui::Image((void*)(intptr_t)primaryAmmoImg->GetTexture(), primaryAmmoImgSize);
    
    // sec weapon
    ImGui::SetCursorScreenPos({primaryAmmoCursor.x - doubleItemSize.x - padBig, primaryAmmoCursor.y});
    ImVec2 secCursor = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(secCursor, ImVec2(secCursor.x + doubleItemSize.x, secCursor.y + itemSize.y), bg);
    auto secImg = ResourcesManager::Get()->find<Texture>("pistol_icon");
    ImVec2 secImgSize = {(float)secImg->GetWidth(), (float)secImg->GetHeight()};
    ImGui::SetCursorScreenPos({secCursor.x + (doubleItemSize.x / 2 - secImgSize.x / 2), secCursor.y + (doubleItemSize.y / 2 - secImgSize.y / 2)});
    ImGui::Image((void*)(intptr_t)secImg->GetTexture(), secImgSize);

    //sec ammo
    ImGui::SetCursorScreenPos({secCursor.x - pad - itemSize.x, secCursor.y});
    ImVec2 secAmmoCursor = ImGui::GetCursorScreenPos();
    const char *secAmmoText = "256";
    ImVec2 secAmmoSize = ImGui::CalcTextSize(secAmmoText);
    ImGui::SetCursorScreenPos({secAmmoCursor.x + (itemSize.x / 2 - secAmmoSize.x / 2), secAmmoCursor.y + 15});
    ImGui::Text("%s", secAmmoText);
    draw->AddRectFilled(secAmmoCursor, ImVec2(secAmmoCursor.x + itemSize.x, secAmmoCursor.y + itemSize.y), bg);
    auto secAmmoImg = ResourcesManager::Get()->find<Texture>("ammo_icon");
    ImVec2 secAmmoImgSize = {(float)secAmmoImg->GetWidth(), (float)secAmmoImg->GetHeight()};
    ImGui::SetCursorScreenPos({secAmmoCursor.x + (itemSize.x / 2 - secAmmoImgSize.x / 2), secAmmoCursor.y + (itemSize.y / 2 - secAmmoImgSize.y / 2) + 15});
    ImGui::Image((void*)(intptr_t)secAmmoImg->GetTexture(), secAmmoImgSize);
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
