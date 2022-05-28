#pragma once

#include "VectorPosition2d.hpp"

namespace mtEngine
{
  struct Coord2Df
  {
    float topLeftX, topLeftY, btmRightX, btmRightY = 0.0f;

    Coord2Df &operator=(Pos2Df pos)
    {
      topLeftX = pos.x1;
      topLeftY = pos.y1;
      btmRightX = pos.x1;
      btmRightY = pos.y2;

      return *this;
    }
  };
} // namespace mtEngine
