#include "HUDLayout.hpp"

namespace Game
{
  HUDLayout::HUDLayout()
  {
    slots = std::make_unique<SlotsLayout>(UNIT_SIZE, ITEMS_GAP);
  };

  HUDLayout::~HUDLayout()
  {
    Shutdown();
  }

  void HUDLayout::RegisterDocks()
  {
    CanvasCalcSizes();
    AddBottom();
  }

  void HUDLayout::Shutdown()
  {
    position = 0;
    padding = 0;
    slots = nullptr;
  }

  void HUDLayout::AddBottom()
  {
    bottom.margin = padding;
    bottom.size = {_canvas.innerSize.x, DEFAULT_HEIGHT};

    Coord2Df &left = bottom.LeftRowBox;
    left.topLeftX = _canvas.inner.topLeftX;
    left.topLeftY = _canvas.inner.topLeftY + _canvas.innerSize.y - bottom.size.y;
    left.btmRightX = _canvas.innerSize.x / 2;
    left.btmRightY = left.topLeftY + UNIT_SIZE.y;

    mtVec2f &cursorLeft = bottom.cursorLeft;
    cursorLeft.x = left.topLeftX;
    cursorLeft.y = left.topLeftY;

    Coord2Df &right = bottom.RightRowBox;
    right.topLeftX = _canvas.innerSize.x / 2;
    right.topLeftY = _canvas.inner.btmRightY - bottom.size.y;
    right.btmRightX = _canvas.inner.btmRightX;
    right.btmRightY = _canvas.inner.btmRightY;

    mtVec2f &cursorRight = bottom.cursorRight;
    cursorRight.x = right.btmRightX;
    cursorRight.y = right.btmRightY - UNIT_SIZE.y;

    slots->left = cursorLeft;
    slots->right = cursorRight;
    slots->AddSlotALeft("health");
    slots->AddSlotBLeft("armor");
    slots->AddSlotCLeft("power");
    slots->AddSlotARight("weapon_primary");
    slots->AddSlotBRight("ammo_primary");
    slots->AddSlotCRight("weapon_secondary");
    slots->AddSlotDRight("ammo_secondary");
    bottom.slots = &slots->getSlots();
  }

  void HUDLayout::CanvasCalcSizes()
  {
    Coord2Df &view = _canvas.viewport;
    view = canvas;
    _canvas.viewportSize = {
        view.btmRightX - view.topLeftX, view.btmRightY - view.topLeftY};

    Coord2Df &inner = _canvas.inner;
    inner.topLeftX = view.topLeftX + padding.lft;
    inner.topLeftY = view.topLeftY + padding.up;
    inner.btmRightX = view.btmRightX - padding.rgt;
    inner.btmRightY = view.btmRightY - padding.dwn;

    _canvas.innerSize = {
        inner.btmRightX - inner.topLeftX, inner.btmRightY - inner.topLeftY};
  }

  HUDLayout::Bottom &HUDLayout::GetBottom()
  {
    return bottom;
  }
} // namespace Game