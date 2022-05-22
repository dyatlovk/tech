#include <gtest/gtest.h>

#include <Gui/Math.hpp>
#include <States/GameStates.hpp>
#include <Scenes/World/Gui/HUD/HUDLayout.hpp>

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(GameStates, string)
{
  auto player = Game::GameStates::ToString(5);
  EXPECT_EQ(player, "Player");

  auto pause = Game::GameStates::ToString(6);
  EXPECT_EQ(pause, "PauseMenu");

  auto inv = Game::GameStates::ToString(8);
  EXPECT_EQ(inv, "Inventory");

  auto def = Game::GameStates::ToString(10);
  EXPECT_EQ(def, "Default");
}

TEST(GameMath, divide_rectangle)
{
  float w = Game::divide_rectangle(2, 5, 25);
  EXPECT_EQ(w, 10);

  float w0 = Game::divide_rectangle(0, 5, 25);
  EXPECT_EQ(w0, 25);
}

TEST(GameGui, canvas)
{
  auto layout = std::make_shared<Game::HUDLayout>();
  layout->canvas.topLeftX = 0.0f;
  layout->canvas.topLeftY = 0.0f;
  layout->canvas.btmRightX = 1000.0f;
  layout->canvas.btmRightY = 1000.0f;
  layout->padding = 20.0f;
  layout->CanvasCalcSizes();
  auto canvas = layout->GetCanvas();

  EXPECT_EQ(canvas.inner.topLeftX, 20.0f);
  EXPECT_EQ(canvas.inner.topLeftY, 20.0f);
  EXPECT_EQ(canvas.inner.btmRightX, 980.0f);
  EXPECT_EQ(canvas.inner.btmRightY, 980.0f);

  EXPECT_EQ(canvas.innerSize.x, 960.0f);
  EXPECT_EQ(canvas.innerSize.y, 960.0f);

  EXPECT_EQ(canvas.viewportSize.x, 1000.0f);
  EXPECT_EQ(canvas.viewportSize.y, 1000.0f);

  EXPECT_EQ(canvas.viewport.topLeftX, 0.0f);
  EXPECT_EQ(canvas.viewport.topLeftY, 0.0f);
  EXPECT_EQ(canvas.viewport.btmRightX, 1000.0f);
  EXPECT_EQ(canvas.viewport.btmRightY, 1000.0f);
}
