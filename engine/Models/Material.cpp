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

    const std::string p(RESOURCES);
    const auto textureId = matSpec.pbrMetallicRoughness->baseColorTexture->index;
    const auto textureSpec = GetTextureSpec(textureId, spec);
    const auto imageId = *textureSpec.source;
    const auto imagesSpec = GetImagesSpec(imageId, spec);
    const auto imagePath = p + *matSpec.extras->textures_path + "/" + *imagesSpec.uri;
    auto res = std::make_shared<Material>(Texture::Create(*imagesSpec.name, imagePath), Shader::CreateDefault());
    res->m_gltfSpec = spec;
    res->_isDoubleSides = CheckIsDoubleSided(textureId, spec);
    res->_isDefault = false;
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

  auto Material::GetTextureSpec(const unsigned int id, const Files::FileGltf::Spec &spec) -> Files::Textures::Item
  {
    const auto s = spec.textures->GetItems();
    return s->at(id);
  }

  auto Material::GetImagesSpec(const unsigned int id, const Files::FileGltf::Spec &spec) -> Files::Images::Item
  {
    const auto s = spec.images->GetItems();
    return s->at(id);
  }

  auto Material::CheckIsDoubleSided(const unsigned int id, const Files::FileGltf::Spec &spec) -> const bool
  {
    const auto s = spec.materials->GetItems();

    return s.at(id).doubleSided;
  }
} // namespace mtEngine
