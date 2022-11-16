#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb/stb_image.h"

namespace mtEngine
{
  Texture::Texture() = default;

  std::shared_ptr<Texture> Texture::Create(const std::string &name, const std::string &path, bool async)
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Texture>(name)) return resource;

    auto resource = std::make_shared<Texture>();
    resource->file = new File();
    resource->file->Load(path);
    resource->LoadFromMemory(resource->file->GetBuffer());
    
    mgr->add(name, std::dynamic_pointer_cast<Resource>(resource));

    PLOGD << "texture " << name << " created...";
    return resource;
  }

  bool Texture::LoadTextureFromFile(const std::string &filename)
  {
    image_data = stbi_load(filename.c_str(), &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr) return false;

    out_width = image_width;
    out_height = image_height;

    return true;
  }

  bool Texture::LoadFromMemory(const std::string &buf)
  {
    if(!buf.c_str()) return false;

    unsigned char const *content = (unsigned char*)buf.c_str();
    image_data = stbi_load_from_memory(content, buf.size(), &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr) return false;

    out_width = image_width;
    out_height = image_height;

    return true;
  }

  void Texture::Update()
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(isTextureReady) return;
    if(!file->isWorkReady()) return;

    GenerateTexture(texture);
    CleanData();
    isTextureReady = true;
    delete file;
  }

  void Texture::GenerateTexture(GLuint &image_texture)
  {
    // Create a OpenGL texture identifier
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Same

    // Upload pixels into texture
    #if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
      glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    #endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  void Texture::CleanData()
  {
    stbi_image_free(image_data);
  }
} // namespace mtEngine
