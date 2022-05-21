#pragma once

#include <GL/gl.h>
#include <memory>
#include <string>

#include "Resources/Resource.hpp"
#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
  class Texture : public Resource
  {
  public:
    Texture();

    using TexturePtr = std::shared_ptr<Texture>;

    static std::shared_ptr<Texture> Create(const std::string &name, const std::string &path);

    GLuint GetTexture() { return texture; };
    int GetWidth() { return width; };
    int GetHeight() { return height; };

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Texture);
    }

    bool LoadTextureFromFile(const std::string &filename);

  private:
    GLuint texture{};
    int width{};
    int height{};
  };
} // namespace mtEngine
