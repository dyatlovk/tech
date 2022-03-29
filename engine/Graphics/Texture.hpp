#pragma once

#include <GL/gl.h>
#include <string>

namespace mtEngine
{
  class Texture
  {
    public:
      Texture() = default;
      ~Texture() = default;

      bool LoadTextureFromFile(const std::string &filename, GLuint* out_texture, int* out_width, int* out_height);
  };
} // namespace mtEngine
