#pragma once
#include "Scenes/World/Gui/HUD/HUDLayout.hpp"
#include "gtest/gtest.h"

namespace GameTest
{
  class HUDLayoutTest : public ::testing::Test
  {
  protected:
    HUDLayoutTest() = default;

    ~HUDLayoutTest() override = default;

    struct Bottom
    {
      mtVec2f size{};
      Box2Df margin{};
      Box2Df padding{};
      mtVec2f cursorLeft{};
      mtVec2f cursorRight{};
      Coord2Df LeftRowBox = {0};
      Coord2Df RightRowBox = {0};
    } _expectedBottomDock{};

    struct Canvas
    {
      Coord2Df viewport;
      Coord2Df inner;
      mtVec2f viewportSize;
      mtVec2f innerSize;
    } _expectedCanvas{};

    void SetUp() override
    {
      layout = std::make_shared<Game::HUDLayout>();
      layout->canvas.topLeftX = 0.0f;
      layout->canvas.topLeftY = 0.0f;
      layout->canvas.btmRightX = 1000.0f;
      layout->canvas.btmRightY = 1000.0f;
      layout->padding = 20.0f;
      ExpectedCanvas();
      ExpectedBottom();
    }

    std::shared_ptr<Game::HUDLayout> layout;

  private:
    void ExpectedCanvas()
    {
      _expectedCanvas.viewport.topLeftX = 0.0f;
      _expectedCanvas.viewport.topLeftY = 0.0f;
      _expectedCanvas.viewport.btmRightX = 1000.0f;
      _expectedCanvas.viewport.btmRightY = 1000.0f;
      _expectedCanvas.viewportSize.x = 1000.0f;
      _expectedCanvas.viewportSize.y = 1000.0f;
      _expectedCanvas.inner.topLeftX = 20.0f;
      _expectedCanvas.inner.topLeftY = 20.0f;
      _expectedCanvas.inner.btmRightX = 980.0f;
      _expectedCanvas.inner.btmRightY = 980.0f;
      _expectedCanvas.innerSize.x = 960.0f;
      _expectedCanvas.innerSize.y = 960.0f;
    }

    void ExpectedBottom()
    {
      _expectedBottomDock.margin.lft = 20.0f;
      _expectedBottomDock.margin.up = 0.0f;
      _expectedBottomDock.margin.rgt = 20.0f;
      _expectedBottomDock.margin.dwn = 20.0f;

      _expectedBottomDock.size.x = 920.0f;
      _expectedBottomDock.size.y = 80.0f;
      _expectedBottomDock.cursorLeft.x = 40.0f;
      _expectedBottomDock.cursorLeft.y = 880.0f;

      _expectedBottomDock.LeftRowBox.topLeftX = 40.0f;
      _expectedBottomDock.LeftRowBox.topLeftY = 880.0f;
      _expectedBottomDock.LeftRowBox.btmRightX = 500.0f;
      _expectedBottomDock.LeftRowBox.btmRightY = 960.0f;

      _expectedBottomDock.cursorRight.x = 960.0f;
      _expectedBottomDock.cursorRight.y = 880.0f;
      _expectedBottomDock.RightRowBox.topLeftX = 500.0f;
      _expectedBottomDock.RightRowBox.topLeftY = 880.0f;
      _expectedBottomDock.RightRowBox.btmRightX = 960.0f;
      _expectedBottomDock.RightRowBox.btmRightY = 960.0f;
    }
  };
} // namespace GameTest
