#include "SlotsContent.hpp"
#include "Guis/IconsFontAwesome6.h"
#include "Resources/ResourcesManager.hpp"
#include "Guis/Font.hpp"

namespace Game
{
  void SlotsContent::UpdateArmor(int value, std::shared_ptr<HUDLayout> layout)
  {
    auto content = std::make_shared<SlotsContent>();
    content->layout = std::move(layout);
    auto bottom = content->layout->GetBottom();

    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.6));
    ImDrawList *draw = ImGui::GetWindowDrawList();

    auto item = bottom.slots->leftSlotB;
    draw->AddRectFilled({item->box.topLeftX, item->box.topLeftY},
        {item->box.btmRightX, item->box.btmRightY}, bg);

    const char *HealthIcon = ICON_FA_USER_SHIELD;
    const std::string HealthText = std::to_string(value);
    ImVec2 HealthTextSize = ImGui::CalcTextSize(HealthText.c_str());
    ImVec2 HealthIconSize = ImGui::CalcTextSize(HealthIcon);

    ImFont *iconFont = ResourcesManager::Get()->find<Font>("icons")->GetFont();
    ImFont *boldFont = ResourcesManager::Get()->find<Font>("ui_bold")->GetFont();

    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x / 2 - HealthIconSize.x / 2 - 6, item->cursor.y +  item->size.y / 2 - HealthIconSize.y - 5});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", HealthIcon);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x / 2 - HealthTextSize.x / 2, item->cursor.y + item->size.y / 2 - HealthTextSize.y / 2 + 15});
    ImGui::PushFont(boldFont);
    ImGui::TextColored(textColor, "%s", HealthText.c_str());
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x + 5, item->cursor.y});
  }

  void SlotsContent::UpdateHealth(int value, std::shared_ptr<HUDLayout> layout) {
    auto content = std::make_shared<SlotsContent>();
    content->layout = std::move(layout);
    auto bottom = content->layout->GetBottom();

    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.6));
    ImDrawList *draw = ImGui::GetWindowDrawList();

    auto health = bottom.slots->leftSlotA;
    draw->AddRectFilled({health->box.topLeftX, health->box.topLeftY},
        {health->box.btmRightX, health->box.btmRightY}, bg);

    const char *HealthIcon = ICON_FA_HEART_PULSE;
    const std::string HealthText = std::to_string(value);
    ImVec2 HealthTextSize = ImGui::CalcTextSize(HealthText.c_str());
    ImVec2 HealthIconSize = ImGui::CalcTextSize(HealthIcon);

    ImFont *iconFont = ResourcesManager::Get()->find<Font>("icons")->GetFont();
    ImFont *boldFont = ResourcesManager::Get()->find<Font>("ui_bold")->GetFont();

    ImGui::SetCursorScreenPos({health->cursor.x + health->size.x / 2 - HealthIconSize.x / 2 - 6, health->cursor.y +  health->size.y / 2 - HealthIconSize.y - 5});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", HealthIcon);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({health->cursor.x + health->size.x / 2 - HealthTextSize.x / 2, health->cursor.y + health->size.y / 2 - HealthTextSize.y / 2 + 15});
    ImGui::PushFont(boldFont);
    ImGui::TextColored(textColor, "%s", HealthText.c_str());
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({health->cursor.x + health->size.x + 5, health->cursor.y});
  }

  void SlotsContent::UpdatePower(int value, std::shared_ptr<HUDLayout> layout) {
    auto content = std::make_shared<SlotsContent>();
    content->layout = std::move(layout);
    auto bottom = content->layout->GetBottom();

    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.6));
    ImDrawList *draw = ImGui::GetWindowDrawList();

    auto item = bottom.slots->leftSlotC;
    draw->AddRectFilled({item->box.topLeftX, item->box.topLeftY},
        {item->box.btmRightX, item->box.btmRightY}, bg);

    const char *HealthIcon = ICON_FA_PERSON_RUNNING;
    const std::string HealthText = std::to_string(value);
    ImVec2 HealthTextSize = ImGui::CalcTextSize(HealthText.c_str());
    ImVec2 HealthIconSize = ImGui::CalcTextSize(HealthIcon);

    ImFont *iconFont = ResourcesManager::Get()->find<Font>("icons")->GetFont();
    ImFont *boldFont = ResourcesManager::Get()->find<Font>("ui_bold")->GetFont();

    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x / 2 - HealthIconSize.x / 2 - 6, item->cursor.y +  item->size.y / 2 - HealthIconSize.y - 5});
    ImGui::PushFont(iconFont);
    ImGui::TextColored(textColor, "%s", HealthIcon);
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x / 2 - HealthTextSize.x / 2, item->cursor.y + item->size.y / 2 - HealthTextSize.y / 2 + 15});
    ImGui::PushFont(boldFont);
    ImGui::TextColored(textColor, "%s", HealthText.c_str());
    ImGui::PopFont();
    ImGui::SetCursorScreenPos({item->cursor.x + item->size.x + 5, item->cursor.y});
  }

  void SlotsContent::UpdateWeaponPrimary(std::shared_ptr<HUDLayout> layout)
  {
    auto content = std::make_shared<SlotsContent>();
    content->layout = std::move(layout);
    auto bottom = content->layout->GetBottom();

    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.6));
    ImDrawList *draw = ImGui::GetWindowDrawList();

    auto item = bottom.slots->rightSlotA;
    draw->AddRectFilled({item->box.topLeftX, item->box.topLeftY},
        {item->box.btmRightX, item->box.btmRightY}, bg);
  }

  void SlotsContent::UpdateWeaponSecondary(int value, std::shared_ptr<HUDLayout> layout)
  {

  }

  void SlotsContent::UpdateArmorPrimary(int value, std::shared_ptr<HUDLayout> layout)
  {
    auto content = std::make_shared<SlotsContent>();
    content->layout = std::move(layout);
    auto bottom = content->layout->GetBottom();

    ImVec4 textColor = ImVec4(1.0, 0.92, 0.65, 1.0);
    const ImU32 bg = ImColor(ImVec4(0.17, 0.17, 0.17, 0.6));
    ImDrawList *draw = ImGui::GetWindowDrawList();

    auto item = bottom.slots->rightSlotB;
    draw->AddRectFilled({item->box.topLeftX, item->box.topLeftY},
        {item->box.btmRightX, item->box.btmRightY}, bg);
  }

  void SlotsContent::UpdateArmorSecondary(int value, std::shared_ptr<HUDLayout> layout)
  {
  }
} // namespace Game
