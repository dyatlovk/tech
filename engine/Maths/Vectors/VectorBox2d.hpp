#pragma once

namespace mtEngine
{
  struct Box2Df
  {
    float lft, up, rgt, dwn;

    Box2Df &operator=(float size)
    {
      lft = rgt = up = dwn = size;

      return *this;
    };
  };
} // namespace mtEngine
