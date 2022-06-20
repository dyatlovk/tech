#define STB_IMAGE_IMPLEMENTATION
#include "Texture.hpp"

#include "Devices/Window.hpp"
#include "third_party/stb/stb_image.h"

namespace mtEngine
{
  Texture::Texture() = default;

  std::shared_ptr<Texture> Texture::Create(const std::string &name, const std::string &path)
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Texture>(name)) return resource;

    auto resource = std::make_shared<Texture>();
    glfwMakeContextCurrent(Window::Get()->GetWindow());
    resource->LoadTextureFromFile(path);
    mgr->add(name, std::dynamic_pointer_cast<Resource>(resource));

    return resource;
  }

  bool Texture::LoadTextureFromFile(const std::string &filename)
  {
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename.c_str(), &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
      return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    stbi_image_free(image_data);
    
    texture = image_texture;
    width = image_width;
    height = image_height;

    return true;
  }
} // namespace mtEngine
