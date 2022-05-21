#pragma once

namespace mtEngine
{
  struct mtVec2f;
  struct mtVec2i;

  struct mtVec2f
  {
    float x, y;
    mtVec2f &operator=(float size)
    {
      x = size;
      y = size;
      return *this;
    };

    mtVec2f &operator=(int size)
    {
      x = (float)size;
      y = (float)size;
      return *this;
    }

    mtVec2f &operator=(mtVec2f val)
    {
      x = val.x;
      y = val.y;
      return *this;
    }
  };

  struct mtVec2i
  {
    int x, y;
    mtVec2i &operator=(float size)
    {
      x = (int)size;
      y = (int)size;
      return *this;
    };

    mtVec2i &operator=(int size)
    {
      x = y = size;
      return *this;
    }

    mtVec2i &operator=(mtVec2i val)
    {
      x = val.x;
      y = val.y;
      return *this;
    }
  };
}
