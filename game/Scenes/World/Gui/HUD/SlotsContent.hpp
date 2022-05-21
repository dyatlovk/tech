#pragma once

#include "Utils/NonCopyable.hpp"
#include "HUDLayout.hpp"
#include "Guis/Imgui.hpp"

namespace Game
{
  class SlotsContent : public NonCopyable
  {
  public:
    SlotsContent() = default;
    ~SlotsContent() override = default;

    void static UpdateArmor(int value, std::shared_ptr<HUDLayout> layout);
    void static UpdateHealth(int value, std::shared_ptr<HUDLayout> layout);
    void static UpdatePower(int value, std::shared_ptr<HUDLayout> layout);
    void static UpdateWeaponPrimary(std::shared_ptr<HUDLayout> layout);
    void static UpdateWeaponSecondary(int value, std::shared_ptr<HUDLayout> layout);
    void static UpdateArmorPrimary(int value, std::shared_ptr<HUDLayout> layout);
    void static UpdateArmorSecondary(int value, std::shared_ptr<HUDLayout> layout);

  public:
    std::shared_ptr<HUDLayout> layout;
  };
} // namespace mtEngine
