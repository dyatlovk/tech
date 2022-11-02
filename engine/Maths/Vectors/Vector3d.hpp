#pragma once

namespace mtEngine
{
  struct mtVec3f
  {
    float x, y, z;
    mtVec3f &operator=(float size)
    {
      x = y = z = size;

      return *this;
    };

    mtVec3f &operator=(int size)
    {
      x = y = z = (float)size;

      return *this;
    };

    mtVec3f &operator=(mtVec3f val)
    {
      x = val.x;
      y = val.y;
      z = val.z;

      return *this;
    }

    mtVec3f &operator*=(float val)
    {
      x = val * x;
      y = val * y;
      z = val * z;

      return *this;
    }
  };

  struct mtVec3i
  {
    float x, y, z;
    mtVec3i &operator=(float size)
    {
      x = y = z = (int)size;

      return *this;
    };

    mtVec3i &operator=(int val)
    {
      x = y = z = val;

      return *this;
    };

    mtVec3i &operator=(mtVec3i val)
    {
      x = val.x;
      y = val.y;
      z = val.z;

      return *this;
    }
  };
} // namespace mtEngine
