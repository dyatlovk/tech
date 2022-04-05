#pragma once

namespace Game
{
  static constexpr float divide_rectangle(unsigned int size, float padding, float width)
  {
    if (size == 0)
    {
      return width;
    }
    return (width - (size - 1) * padding) / size;
  }
} // namespace Game
