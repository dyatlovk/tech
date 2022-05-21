#pragma once

#include <memory>
#include <vector>

#include "Maths/Vectors/Coord2d.hpp"
#include "Maths/Vectors/Vector2d.hpp"
#include "Maths/Vectors/VectorBox2d.hpp"
#include "Maths/Vectors/VectorPosition2d.hpp"
#include "SlotsLayout.hpp"
#include "Utils/NonCopyable.hpp"

using namespace mtEngine;

namespace Game
{
  enum HUDPosition
  {
    Position_None = 0,
    Position_Right = 1 << 0,
    Position_Left = 1 << 1,
    Position_Top = 1 << 2,
    Position_Bottom = 1 << 3,
  };

  class HUDLayout : public NonCopyable
  {
  private:
    struct Bottom
    {
      mtVec2f size;
      Box2Df margin;
      Box2Df padding;
      mtVec2f cursorLeft;
      mtVec2f cursorRight;
      Coord2Df LeftRowBox = {0};
      Coord2Df RightRowBox = {0};
      SlotsLayout::HUDSlots *slots{};
    };

    struct Canvas
    {
      Coord2Df viewport;
      Coord2Df inner;
      mtVec2f viewportSize;
      mtVec2f innerSize;
    } _canvas{};

  public:
    // row width in percent
    static constexpr float BOTTOM_LEFT_MAX_WIDTH = 50.0f;
    static constexpr float BOTTOM_RIGHT_MAX_WIDTH = 50.0f;
    static constexpr mtVec2f UNIT_SIZE = {80.0f, 80.0f};
    static constexpr int ITEMS_GAP = 5;
    static constexpr int DEFAULT_HEIGHT = UNIT_SIZE.y;

    HUDLayout();

    ~HUDLayout() override;

    void RegisterDocks();

    void CanvasCalcSizes();

    void Shutdown();

    Bottom &GetBottom();

  public:
    Box2Df padding = {0.0f};
    Coord2Df canvas = {0.0f};

  private:
    void AddBottom();

  private:
    int position = 0;
    Bottom bottom{};
    std::unique_ptr<SlotsLayout> slots;
  };
} // namespace Game
