#pragma once

#include "Vector4d.hpp"

namespace mtEngine
{
  struct Pos2Di;
  struct Pos2Df;

  struct Pos2Di
  {
    int x1, y1, x2, y2;
    Pos2Di &operator=(int v)
    {
      x1 = x2 = y1 = y2 = v;

      return *this;
    }

    Pos2Di &operator=(float v)
    {
      x1 = x2 = y1 = y2 = (int)v;

      return *this;
    }

    Pos2Di &operator=(Pos2Di v)
    {
      x1 = v.x1;
      x2 = v.x2;
      y1 = v.y1;
      y2 = v.y2;

      return *this;
    }
  };

  struct Pos2Df
  {
    float x1, y1, x2, y2;
    Pos2Df &operator=(int v)
    {
      x1 = x2 = y1 = y2 = (float)v;

      return *this;
    }

    Pos2Df &operator=(float v)
    {
      x1 = v;
      x2 = v;
      y1 = v;
      y2 = v;

      return *this;
    }

    Pos2Df &operator=(Pos2Df v)
    {
      x1 = v.x1;
      x2 = v.x2;
      y1 = v.y1;
      y2 = v.y2;

      return *this;
    }

    Pos2Df &operator=(mtVec2f v)
    {
      x1 = 0.0f;
      y1 = 0.0f;
      x2 = v.x;
      y2 = v.y;

      return *this;
    }

    Pos2Df &operator=(mtVec4f v)
    {
      x1 = v.x;
      x2 = v.y;
      y1 = v.z;
      y2 = v.w;

      return *this;
    }
  };
} // namespace mtEngine
