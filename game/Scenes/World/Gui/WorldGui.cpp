#include "WorldGui.hpp"

#include "Guis/Font.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Scenes/MainMenu/MainMenu.hpp"
#include "Gui/Math.hpp"
#include "HUD/SlotsContent.hpp"

namespace Game
{
  WorldGui::WorldGui()
  {
    hudLayout = std::make_shared<HUDLayout>();
  };

  void WorldGui::PlayerInfo()
  {
    mtVec2f vSize = {ImGui::GetMainViewport()->Size.x, ImGui::GetMainViewport()->Size.y};
    hudLayout->canvas.topLeftX = 0.0f;
    hudLayout->canvas.topLeftY = 0.0f;
    hudLayout->canvas.btmRightX = vSize.x;
    hudLayout->canvas.btmRightY = vSize.y;
    hudLayout->padding = 0;
    hudLayout->RegisterDocks();

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoBackground;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});

    auto bottom = hudLayout->GetBottom();
    ImGui::SetNextWindowPos({bottom.LeftRowBox.topLeftX, bottom.LeftRowBox.topLeftY}, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize({bottom.size.x, bottom.size.y});

    ImGui::Begin("##player_info", nullptr, flags);
    SlotsContent::UpdateHealth(54, hudLayout);
    SlotsContent::UpdateArmor(90, hudLayout);
    SlotsContent::UpdatePower(81, hudLayout);
    SlotsContent::UpdateWeaponPrimary(hudLayout);
    SlotsContent::UpdateArmorPrimary(180, hudLayout);
    ImGui::End();
    ImGui::PopStyleVar();
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
    const char *fourthText = "20 L_SLOT_A";
    ImVec2 fouthTextSize = ImGui::CalcTextSize(fourthText);
    ImGui::SetCursorScreenPos({p.x + w / 2 - fouthTextSize.x / 2, p.y + heightItem / 2 - fouthTextSize.y / 2});
    ImGui::Text("%s", fourthText);

    ImGui::SetCursorScreenPos({panelCursor.x, panelCursor.y + heightItem + padding});
  }

  void WorldGui::Weapons() const
  {
    static ImVec4 bgf = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
    const ImU32 bg = ImColor(bgf);

    ImDrawList *draw = ImGui::GetWindowDrawList();
    auto win_size = ImGui::GetCurrentWindow()->WorkRect;

    float width = win_size.GetWidth();
    float height = 160;
    ImVec2 p = ImGui::GetCursorScreenPos();
    draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), bg); //bg

    ImGui::SetCursorScreenPos({p.x + padding, p.y + padding});
    float widthWeaponsItems = Game::divide_rectangle(2, padding, win_size.GetWidth() - 20);
    float heightWeaponsItems = 140;
    p = ImGui::GetCursorScreenPos();
    ImVec2 primaryCursor = p;
    draw->AddRectFilled(p, ImVec2(p.x + widthWeaponsItems, p.y + heightWeaponsItems), ImColor(ImVec4(0.23f, 0.23f, 0.23f, 0.22f))); // inner bg
    auto primaryImg = ResourcesManager::Get()->find<Texture>("vss_icon");
    ImVec2 primaryImgSize = {(float)primaryImg->GetWidth(), (float)primaryImg->GetHeight()};
    ImGui::SetCursorScreenPos({primaryCursor.x + (widthWeaponsItems / 2 - primaryImgSize.x / 2), primaryCursor.y + (heightWeaponsItems / 2 - primaryImgSize.y / 2)});
    ImGui::Image((void*)(intptr_t)primaryImg->GetTexture(), primaryImgSize);

    ImGui::SetCursorScreenPos({p.x + widthWeaponsItems + padding, p.y});
    p = ImGui::GetCursorScreenPos();
    ImVec2 secCursor = p;
    draw->AddRectFilled(p, ImVec2(p.x + widthWeaponsItems, p.y + heightWeaponsItems), ImColor(ImVec4(0.23f, 0.23f, 0.23f, 0.22f)));
    auto secImg = ResourcesManager::Get()->find<Texture>("pistol_icon");
    ImVec2 secImgSize = {(float)secImg->GetWidth(), (float)secImg->GetHeight()};
    ImGui::SetCursorScreenPos({secCursor.x + (widthWeaponsItems / 2 - secImgSize.x / 2), secCursor.y + (heightWeaponsItems / 2 - secImgSize.y / 2)});
    ImGui::Image((void*)(intptr_t)secImg->GetTexture(), secImgSize);

    ImGui::SetCursorScreenPos({panelCursor.x, p.y + height});
  }

  void WorldGui::Items() const
  {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList *draw = ImGui::GetWindowDrawList();
    auto win_size = ImGui::GetCurrentWindow()->WorkRect;
    float width = win_size.GetWidth();
    float height = win_size.GetHeight() - p.y + 20.0f;

    // bg
    draw->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImColor(ImVec4(0.12f, 0.12f, 0.12f, 1.0f)));
    ImGui::SetCursorScreenPos({p.x + 10, p.y + 10});
    ImVec2 itemsCursor = ImGui::GetCursorScreenPos();
    ImGuiStyle& style = ImGui::GetStyle();

    // bg inner
    draw->AddRectFilled(itemsCursor, ImVec2(itemsCursor.x + width - 20 - style.ScrollbarSize, itemsCursor.y + height - 20), ImColor(ImVec4(0.10f, 0.10f, 0.10f, 1.0f)));
    ImGui::BeginChild("##Inventory items", ImVec2(width - 20, height - 20));

    // grid
    ///////
    int GRID_SIZE = 17;
    draw->PushClipRect(itemsCursor, {itemsCursor.x + width - 20 - style.ScrollbarSize, itemsCursor.y + height - 20});
    // horizontal
    for(int i = 1; i <= GRID_SIZE; i++)
      draw->AddLine({itemsCursor.x, itemsCursor.y + itemUnitSize.x * i}, {itemsCursor.x + width - 20, itemsCursor.y + itemUnitSize.y * i}, ImColor(ImVec4(0.12f, 0.12f, 0.12f, 1.0f)));

    // vertical
    for(int i = 1; i <= GRID_SIZE; i++)
      draw->AddLine({itemsCursor.x + 60 * i, itemsCursor.y}, {itemsCursor.x + 60 * i, itemsCursor.y + height - 20}, ImColor(ImVec4(0.12f, 0.12f, 0.12f, 1.0f)));
    draw->PopClipRect();

    AddItem(itemsCursor, "armor_icon", 2, 3);
    AddItem({itemsCursor.x + itemUnitSize.x * 2, itemsCursor.y}, "vss_icon", 4, 1);
    AddItem({itemsCursor.x + itemUnitSize.x * 6, itemsCursor.y}, "pistol_icon", 2, 1, true);
    AddItem({itemsCursor.x + itemUnitSize.x * 2, itemsCursor.y + itemUnitSize.y * 1}, "grenade_icon", 1, 1);
    ImGui::EndChild();
  }

  void WorldGui::AddItem(ImVec2 pos, const std::string &imgName, int sizeX, int sizeY, bool hovered) const
  {
    auto iconImg = ResourcesManager::Get()->find<Texture>(imgName);
    if(!iconImg) return;

    ImVec2 size = {itemUnitSize.x * sizeX, itemUnitSize.y * sizeY};
    ImDrawList *draw = ImGui::GetWindowDrawList();
    ImVec2 imgSize = {(float)iconImg->GetWidth(), (float)iconImg->GetHeight()};
    if(hovered) {
        draw->AddRectFilled(pos, {pos.x + size.x, pos.y + size.y}, ImColor(ImVec4(0.31f, 0.43f, 0.33f, 1.0f)));
        draw->AddRect(pos, {pos.x + size.x, pos.y + size.y}, ImColor(ImVec4(0.33f, 0.91f, 0.43f, 1.0f)));
    }
    ImGui::SetCursorScreenPos({pos.x + (size.x / 2 - imgSize.x / 2), pos.y + (size.y / 2 - imgSize.y / 2)});
    ImGui::Image((void*)(intptr_t)iconImg->GetTexture(), imgSize);
  }
} // namespace Game
