#include "SlotsLayout.hpp"

namespace Game
{
  SlotsLayout::SlotsLayout(mtVec2f unitSize, int gap)
  {
    this->unitSize = unitSize;
    this->gap = gap;
  }

  void SlotsLayout::AddSlotALeft(const std::string &name)
  {
    l_slot_a.name = name;
    l_slot_a.size = unitSize;
    l_slot_a.cursor = left;
    l_slot_a.box.topLeftX = l_slot_a.cursor.x;
    l_slot_a.box.topLeftY = l_slot_a.cursor.y;
    l_slot_a.box.btmRightX = l_slot_a.cursor.x + unitSize.x;
    l_slot_a.box.btmRightY = l_slot_a.cursor.y + unitSize.y;
    _slots.leftSlotA = &l_slot_a;
  }

  void SlotsLayout::AddSlotBLeft(const std::string &name)
  {
    l_slot_b.name = name;
    l_slot_b.size = unitSize;
    const mtVec2f cursor = l_slot_b.cursor = {
        l_slot_a.box.btmRightX + (float)gap, l_slot_a.box.topLeftY};
    l_slot_b.box.topLeftX = cursor.x;
    l_slot_b.box.topLeftY = cursor.y;
    l_slot_b.box.btmRightX = cursor.x + unitSize.x;
    l_slot_b.box.btmRightY = cursor.y + unitSize.y;
    _slots.leftSlotB = &l_slot_b;
  }

  void SlotsLayout::AddSlotCLeft(const std::string &name)
  {
    l_slot_c.name = name;
    l_slot_c.size = unitSize;
    const mtVec2f cursor = l_slot_c.cursor = {
        l_slot_b.box.btmRightX + (float)gap, l_slot_b.box.topLeftY};
    l_slot_c.box.topLeftX = cursor.x;
    l_slot_c.box.topLeftY = cursor.y;
    l_slot_c.box.btmRightX = cursor.x + unitSize.x;
    l_slot_c.box.btmRightY = cursor.y + unitSize.y;
    _slots.leftSlotC = &l_slot_c;
  }

  void SlotsLayout::AddSlotARight(const std::string &name)
  {
    r_slot_a.name = name;
    r_slot_a.size = {unitSize.x * 2, unitSize.y};
    r_slot_a.cursor = {right.x - unitSize.x, right.y};
    r_slot_a.box.topLeftX = r_slot_a.cursor.x;
    r_slot_a.box.topLeftY = r_slot_a.cursor.y;
    r_slot_a.box.btmRightX = r_slot_a.cursor.x + unitSize.x * 2;
    r_slot_a.box.btmRightY = r_slot_a.cursor.y + unitSize.y;
    _slots.rightSlotA = &r_slot_a;
  }

  void SlotsLayout::AddSlotBRight(const std::string &name)
  {
    r_slot_b.name = name;
    r_slot_b.size = unitSize;
    const mtVec2f cursor =
        r_slot_b.cursor = {r_slot_a.cursor.x - (float)gap - r_slot_b.size.x,
            r_slot_a.box.topLeftY};
    r_slot_b.box.topLeftX = cursor.x;
    r_slot_b.box.topLeftY = cursor.y;
    r_slot_b.box.btmRightX = cursor.x + r_slot_b.size.x;
    r_slot_b.box.btmRightY = cursor.y + r_slot_b.size.y;
    _slots.rightSlotB = &r_slot_b;
  }

  void SlotsLayout::AddSlotCRight(const std::string &name)
  {
    r_slot_c.name = name;
    r_slot_c.size = {unitSize.x * 2, unitSize.y};
    const mtVec2f cursor =
        r_slot_c.cursor = {r_slot_b.cursor.x - (float)gap - r_slot_c.size.x,
            r_slot_b.box.topLeftY};
    r_slot_c.box.topLeftX = cursor.x;
    r_slot_c.box.topLeftY = cursor.y;
    r_slot_c.box.btmRightX = cursor.x + r_slot_c.size.x;
    r_slot_c.box.btmRightY = cursor.y + r_slot_c.size.y;
    _slots.rightSlotC = &r_slot_c;
  }
  void SlotsLayout::AddSlotDRight(const std::string &name)
  {
    r_slot_d.name = name;
    r_slot_d.size = unitSize;
    const mtVec2f cursor =
        r_slot_d.cursor = {r_slot_c.cursor.x - (float)gap - r_slot_d.size.x,
            r_slot_c.box.topLeftY};
    r_slot_d.box.topLeftX = cursor.x;
    r_slot_d.box.topLeftY = cursor.y;
    r_slot_d.box.btmRightX = cursor.x + r_slot_d.size.x;
    r_slot_d.box.btmRightY = cursor.y + r_slot_d.size.y;
    _slots.rightSlotD = &r_slot_d;
  }
} // namespace Game
