#pragma once

#include <memory>
#include <string>

#include "Devices/Window.hpp"
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
    int GetWidth() { return out_width; };
    int GetHeight() { return out_height; };

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Texture);
    }

    bool LoadTextureFromFile(const std::string &filename);
    bool LoadFromMemory(const std::string &buf);

  private:
    void GenerateTexture(GLuint &image_texture);

  private:
    GLuint texture = 0;
    int out_width = 0;
    int out_height = 0;

    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data;
  };
} // namespace mtEngine
