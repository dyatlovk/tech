#include "Material.hpp"

namespace mtEngine
{
  Material::Material(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
      : m_texture(std::move(texture))
      , m_shader(std::move(shader))
      , _isDefault(true)
      , _isDoubleSides(false)
  {
  }

  auto Material::Create(const uint16_t id, const Files::FileGltf::Spec &spec) -> std::shared_ptr<Material>
  {
    const auto matSpec = GetMaterialSpec(id, spec);
    const auto name = matSpec.name;

    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Material>(*name))
      return resource;

    const auto texInfo = GetTextureInfo(matSpec, spec);
    std::shared_ptr<Texture> texture = nullptr;
    if(texInfo) {
      texture = Texture::Create(texInfo->name, texInfo->path);
    }

    const auto shader = CreateShader(matSpec);
    auto res = std::make_shared<Material>(texture, shader);
    res->m_gltfSpec = spec;
    if(texture) {
      res->_isDoubleSides = CheckIsDoubleSided(texInfo->specId, spec);
      res->_isDefault = false;
    }
    mgr->add(*name, std::dynamic_pointer_cast<Resource>(res));

    return res;
  }

  auto Material::CreateDefault() -> std::shared_ptr<Material>
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Material>("default"))
      return resource;

    auto res = std::make_shared<Material>(nullptr, Shader::CreateDefault());
    res->_isDefault = true;
    mgr->add("default", res);

    return res;
  }

  void Material::Draw()
  {
    Texture::Unbind();
    if (m_texture)
    {
      m_texture->Update();
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  auto Material::GetMaterialSpec(const unsigned int id, const Files::FileGltf::Spec &spec) -> Files::Materials::Item
  {
    const auto s = spec.materials->GetItems();
    return s.at(id);
  }

  auto Material::GetTextureSpec(const unsigned int id, const Files::FileGltf::Spec &spec) -> Files::Textures::Item*
  {
    const auto s = spec.textures->GetItems();
    if(!s) {
      return nullptr;
    }

    for (size_t i = 0; i < s->size(); i++) {
      if(i == id) {
        return &s->at(id);
      }
    }

    return nullptr;
  }

  auto Material::GetImagesSpec(const unsigned int id, const Files::FileGltf::Spec &spec) -> Files::Images::Item*
  {
    const auto s = spec.images->GetItems();
    if(!s) {
      return nullptr;
    }
    for (size_t i = 0; i < s->size(); i++) {
      if(i == id) {
        return &s->at(id);
      }
    }

    return nullptr;
  }

  auto Material::CheckIsDoubleSided(const unsigned int id, const Files::FileGltf::Spec &spec) -> const bool
  {
    const auto s = spec.materials->GetItems();

    return s.at(id).doubleSided;
  }

  auto Material::CreateShader(const Files::Materials::Item &matSpec) -> std::shared_ptr<Shader> const
  {
    std::shared_ptr<Shader> _m_shader;
    const auto extras = matSpec.extras;
    if(!extras) {
      _m_shader = Shader::CreateDefault();
    }

    const std::string p(RESOURCES);
    if(extras) {
      const auto frag = extras->shader_fs;
      const auto vert = extras->shader_vs;
      const auto pathInfo = File::CreatePathInfo(p + *vert);
      _m_shader = Shader::Create(pathInfo.fileName, p + *vert, p + *frag);
    }

    return _m_shader;
  }

  auto Material::GetTextureInfo(const Files::Materials::Item &matSpec, const Files::FileGltf::Spec &spec) -> Material::TextureInfo* const
  {
    const std::string p(RESOURCES);
    TextureInfo *_texInfo = new TextureInfo();

    if(!matSpec.extras) {
      delete _texInfo;
      return nullptr;
    }

    if(!matSpec.extras->textures_path) {
      delete _texInfo;
      return nullptr;
    }

    if(!matSpec.pbrMetallicRoughness) {
      delete _texInfo;
      return nullptr;
    }

    if(!matSpec.pbrMetallicRoughness->baseColorTexture) {
      delete _texInfo;
      return nullptr;
    }

    const auto textureId = matSpec.pbrMetallicRoughness->baseColorTexture->index;
    const auto textureSpec = GetTextureSpec(textureId, spec);
    if(!textureSpec) {
      delete _texInfo;
      return nullptr;
    }
    _texInfo->specId = textureId;

    if(!textureSpec->source) {
      delete _texInfo;
      return nullptr;
    }

    const auto imageId = *textureSpec->source;
    const auto imagesSpec = GetImagesSpec(imageId, spec);
    if(!imagesSpec) {
      delete _texInfo;
      return nullptr;
    }

    const auto imagePath = p + *matSpec.extras->textures_path + "/" + *imagesSpec->uri;
    _texInfo->path = imagePath;
    _texInfo->name = *imagesSpec->name;

    return _texInfo;
  }
} // namespace mtEngine
