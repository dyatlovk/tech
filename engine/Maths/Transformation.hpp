#pragma once

#include <math.h>

#include "./Vectors/Vector4d.hpp"

namespace mtEngine
{
  struct quatToAxisAngle
  {
    float x, y, z = 0.0f;
    float angle = 1.0f;

    quatToAxisAngle &operator=(mtVec4f val)
    {
      constexpr float PI = 3.14;
      float angle_rad = acos(val.w) * 2;
      float angle_deg = angle_rad * 180 / PI;
      x = val.x / sin(angle_rad / 2);
      y = val.y / sin(angle_rad / 2);
      z = val.z / sin(angle_rad / 2);
      angle = angle_deg;

      return *this;
    }
  };
} // namespace mtEngine
