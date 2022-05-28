#include <Fixtures/HUDLayoutFixture.hpp>

#include "gtest/gtest.h"

namespace GameTest
{
  TEST_F(HUDLayoutTest, canvas)
  {
    layout->CanvasCalcSizes();
    auto canvas = layout->GetCanvas();

    EXPECT_EQ(canvas.inner.topLeftX, _expectedCanvas.inner.topLeftX);
    EXPECT_EQ(canvas.inner.topLeftY, _expectedCanvas.inner.topLeftY);
    EXPECT_EQ(canvas.inner.btmRightX, _expectedCanvas.inner.btmRightX);
    EXPECT_EQ(canvas.inner.btmRightY, _expectedCanvas.inner.btmRightY);

    EXPECT_EQ(canvas.innerSize.x, _expectedCanvas.innerSize.x);
    EXPECT_EQ(canvas.innerSize.y, _expectedCanvas.innerSize.y);

    EXPECT_EQ(canvas.viewportSize.x, _expectedCanvas.viewportSize.x);
    EXPECT_EQ(canvas.viewportSize.y, _expectedCanvas.viewportSize.y);

    EXPECT_EQ(canvas.viewport.topLeftX, _expectedCanvas.viewport.topLeftX);
    EXPECT_EQ(canvas.viewport.topLeftY, _expectedCanvas.viewport.topLeftY);
    EXPECT_EQ(canvas.viewport.btmRightX, _expectedCanvas.viewport.btmRightX);
    EXPECT_EQ(canvas.viewport.btmRightY, _expectedCanvas.viewport.btmRightY);
  }

  TEST_F(HUDLayoutTest, BottomDock)
  {
    layout->RegisterDocks();

    auto bottom = layout->GetBottom();

    EXPECT_EQ(bottom.size.x, _expectedBottomDock.size.x);
    EXPECT_EQ(bottom.size.y, _expectedBottomDock.size.y);

    EXPECT_EQ(bottom.cursorLeft.x, _expectedBottomDock.cursorLeft.x);
    EXPECT_EQ(bottom.cursorLeft.y, _expectedBottomDock.cursorLeft.y);
    EXPECT_EQ(bottom.LeftRowBox.topLeftX, _expectedBottomDock.LeftRowBox.topLeftX);
    EXPECT_EQ(bottom.LeftRowBox.topLeftY, _expectedBottomDock.LeftRowBox.topLeftY);
    EXPECT_EQ(bottom.LeftRowBox.btmRightX, _expectedBottomDock.LeftRowBox.btmRightX);
    EXPECT_EQ(bottom.LeftRowBox.btmRightY, _expectedBottomDock.LeftRowBox.btmRightY);

    EXPECT_EQ(bottom.cursorRight.x, _expectedBottomDock.cursorRight.x);
    EXPECT_EQ(bottom.cursorRight.y, _expectedBottomDock.cursorRight.y);
    EXPECT_EQ(bottom.RightRowBox.topLeftX, _expectedBottomDock.RightRowBox.topLeftX);
    EXPECT_EQ(bottom.RightRowBox.topLeftY, _expectedBottomDock.RightRowBox.topLeftY);
    EXPECT_EQ(bottom.RightRowBox.btmRightX, _expectedBottomDock.RightRowBox.btmRightX);
    EXPECT_EQ(bottom.RightRowBox.btmRightY, _expectedBottomDock.RightRowBox.btmRightY);
  }

  TEST_F(HUDLayoutTest, SlotLeftA)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->leftSlotA->size.x, 80.0f);
    EXPECT_EQ(slots->leftSlotA->size.y, 80.0f);
    EXPECT_EQ(slots->leftSlotA->cursor.x, 40.0f);
    EXPECT_EQ(slots->leftSlotA->cursor.y, 880.0f);
    EXPECT_EQ(slots->leftSlotA->box.topLeftX, 40.0f);
    EXPECT_EQ(slots->leftSlotA->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->leftSlotA->box.btmRightX, 120.0f);
    EXPECT_EQ(slots->leftSlotA->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotLeftB)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->leftSlotB->size.x, 80.0f);
    EXPECT_EQ(slots->leftSlotB->size.y, 80.0f);
    EXPECT_EQ(slots->leftSlotB->cursor.x, 125.0f);
    EXPECT_EQ(slots->leftSlotB->cursor.y, 880.0f);
    EXPECT_EQ(slots->leftSlotB->box.topLeftX, 125.0f);
    EXPECT_EQ(slots->leftSlotB->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->leftSlotB->box.btmRightX, 205.0f);
    EXPECT_EQ(slots->leftSlotB->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotLeftC)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->leftSlotC->size.x, 80.0f);
    EXPECT_EQ(slots->leftSlotC->size.y, 80.0f);
    EXPECT_EQ(slots->leftSlotC->cursor.x, 210.0f);
    EXPECT_EQ(slots->leftSlotC->cursor.y, 880.0f);
    EXPECT_EQ(slots->leftSlotC->box.topLeftX, 210.0f);
    EXPECT_EQ(slots->leftSlotC->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->leftSlotC->box.btmRightX, 290.0f);
    EXPECT_EQ(slots->leftSlotC->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotRightA)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->rightSlotA->size.x, 160.0f);
    EXPECT_EQ(slots->rightSlotA->size.y, 80.0f);
    EXPECT_EQ(slots->rightSlotA->cursor.x, 800.0f);
    EXPECT_EQ(slots->rightSlotA->cursor.y, 880.0f);
    EXPECT_EQ(slots->rightSlotA->box.topLeftX, 800.0f);
    EXPECT_EQ(slots->rightSlotA->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->rightSlotA->box.btmRightX, 960.0f);
    EXPECT_EQ(slots->rightSlotA->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotRightB)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->rightSlotB->size.x, 80.0f);
    EXPECT_EQ(slots->rightSlotB->size.y, 80.0f);
    EXPECT_EQ(slots->rightSlotB->cursor.x, 715.0f);
    EXPECT_EQ(slots->rightSlotB->cursor.y, 880.0f);
    EXPECT_EQ(slots->rightSlotB->box.topLeftX, 715.0f);
    EXPECT_EQ(slots->rightSlotB->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->rightSlotB->box.btmRightX, 795.0f);
    EXPECT_EQ(slots->rightSlotB->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotRightC)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->rightSlotC->size.x, 160.0f);
    EXPECT_EQ(slots->rightSlotC->size.y, 80.0f);
    EXPECT_EQ(slots->rightSlotC->cursor.x, 550.0f);
    EXPECT_EQ(slots->rightSlotC->cursor.y, 880.0f);
    EXPECT_EQ(slots->rightSlotC->box.topLeftX, 550.0f);
    EXPECT_EQ(slots->rightSlotC->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->rightSlotC->box.btmRightX, 710.0f);
    EXPECT_EQ(slots->rightSlotC->box.btmRightY, 960.0f);
  }

  TEST_F(HUDLayoutTest, SlotRightD)
  {
    layout->RegisterDocks();

    auto slots = layout->GetBottom().slots;

    EXPECT_EQ(slots->rightSlotD->size.x, 80.0f);
    EXPECT_EQ(slots->rightSlotD->size.y, 80.0f);
    EXPECT_EQ(slots->rightSlotD->cursor.x, 465.0f);
    EXPECT_EQ(slots->rightSlotD->cursor.y, 880.0f);
    EXPECT_EQ(slots->rightSlotD->box.topLeftX, 465.0f);
    EXPECT_EQ(slots->rightSlotD->box.topLeftY, 880.0f);
    EXPECT_EQ(slots->rightSlotD->box.btmRightX, 545.0f);
    EXPECT_EQ(slots->rightSlotD->box.btmRightY, 960.0f);
  }
} // namespace GameTest
