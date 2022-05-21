#pragma once

#include "Vector2d.hpp"

namespace mtEngine
{
  struct mtVec4f;
  struct mtVec4i;

  struct mtVec4f
  {
    float x, y, z, w;
    mtVec4f &operator=(float size)
    {
      x = size;
      y = size;
      z = size;
      w = size;
      return *this;
    };

    mtVec4f &operator=(int size)
    {
      x = (float)size;
      y = (float)size;
      z = (float)size;
      w = (float)size;
      return *this;
    }

    mtVec4f &operator=(mtVec4f val)
    {
      x = val.x;
      y = val.y;
      z = val.z;
      w = val.w;
      return *this;
    }

    mtVec4f &operator=(mtVec2f val)
    {
      x = val.x;
      y = val.y;
      z = val.x;
      w = val.y;
      return *this;
    }
  };

  struct mtVec4i
  {
    int x, y, z, w;
    mtVec4i &operator=(float size)
    {
      x = y = z = w = (int)size;
      return *this;
    };

    mtVec4i &operator=(int size)
    {
      x = y = z = w = size;
      return *this;
    }

    mtVec4i &operator=(mtVec4i val)
    {
      x = val.x;
      y = val.y;
      z = val.z;
      w = val.w;
      return *this;
    }

    mtVec4i &operator=(mtVec2i val)
    {
      x = val.x;
      y = val.y;
      z = val.x;
      w = val.y;
      return *this;
    }
  };
} // namespace mtEngine
