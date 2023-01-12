#pragma once

#include "Maths/Vectors/Coord2d.hpp"
#include "Maths/Vectors/Vector2d.hpp"
#include "Utils/NonCopyable.hpp"
#include "string"

using namespace mtEngine;

namespace Game
{
  class SlotsLayout : public NonCopyable
  {
  private:
    struct L_SLOT_A
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } l_slot_a{};

    struct L_SLOT_B
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } l_slot_b{};

    struct L_SLOT_C
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } l_slot_c{};

    struct R_SLOT_A
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } r_slot_a{};

    struct R_SLOT_B
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } r_slot_b{};

    struct R_SLOT_C
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } r_slot_c{};

    struct R_SLOT_D
    {
      std::string name;
      mtVec2f size{};
      mtVec2f cursor{};
      Coord2Df box{};
    } r_slot_d{};

  public:
    explicit SlotsLayout(mtVec2f unitSize, int gap);
    ~SlotsLayout() override = default;

    struct HUDSlots
    {
      L_SLOT_A *leftSlotA{};
      L_SLOT_B *leftSlotB{};
      L_SLOT_C *leftSlotC{};
      R_SLOT_A *rightSlotA{};
      R_SLOT_B *rightSlotB{};
      R_SLOT_C *rightSlotC{};
      R_SLOT_D *rightSlotD{};
    } _slots;

    void AddSlotALeft(const std::string &name);
    void AddSlotBLeft(const std::string &name);
    void AddSlotCLeft(const std::string &name);

    void AddSlotARight(const std::string &name);
    void AddSlotBRight(const std::string &name);
    void AddSlotCRight(const std::string &name);
    void AddSlotDRight(const std::string &name);

    HUDSlots &getSlots() { return _slots; };

  public:
    mtVec2f left{};
    mtVec2f right{};

  private:
    mtVec2f unitSize{};
    int gap;
  };

} // namespace Game
