#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include <Files/FileGltf.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Texture.hpp>
#include <Resources/Resource.hpp>

namespace mtEngine
{
  class Material : public Resource
  {
  private:
    struct TextureInfo;
  public:
    Material(std::shared_ptr<Texture> texture = nullptr, std::shared_ptr<Shader> shader = nullptr);

    static auto Create(const uint16_t id, const Files::FileGltf::Spec &spec) -> std::shared_ptr<Material>;

    static auto CreateDefault() -> std::shared_ptr<Material>;

    void Draw();

    auto GetShader() -> std::shared_ptr<Shader> { return m_shader; }
    auto GetTexture() -> std::shared_ptr<Texture> { return m_texture; }

    const bool isDefault() { return _isDefault; }

    const bool isDoubleSided() { return _isDoubleSides; }

    [[nodiscard]] auto GetTypeIndex() const -> std::type_index override { return typeid(Material); }

  private:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Shader> m_shader;
    Files::FileGltf::Spec m_gltfSpec;
    bool _isDefault;
    bool _isDoubleSides;

    static auto GetMaterialSpec     (const unsigned int id, const Files::FileGltf::Spec &spec                 ) -> Files::Materials::Item;
    static auto GetTextureSpec      (const unsigned int id, const Files::FileGltf::Spec &spec                 ) -> Files::Textures::Item*;
    static auto GetImagesSpec       (const unsigned int id, const Files::FileGltf::Spec &spec                 ) -> Files::Images::Item*;
    static auto CheckIsDoubleSided  (const unsigned int id, const Files::FileGltf::Spec &spec                 ) -> const bool;
    static auto CreateShader        (const Files::Materials::Item &matSpec                                    ) -> std::shared_ptr<Shader> const;
    static auto GetTextureInfo      (const Files::Materials::Item &matSpec, const Files::FileGltf::Spec &spec ) -> TextureInfo* const;

    struct TextureInfo {
      std::string name;
      std::string path;
      unsigned int specId;
    };
  };

} // namespace mtEngine
