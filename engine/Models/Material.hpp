#pragma once

#include <memory>
#include <string>

#include <Graphics/Texture.hpp>
#include <Resources/Resource.hpp>

namespace mtEngine
{
  class Material : public Resource
  {
  public:
    Material() = default;

    static auto Create(const std::string &name, const Texture *texture) -> std::shared_ptr<Material>;

    void Draw();

    [[nodiscard]] auto GetTypeIndex() const -> std::type_index override { return typeid(Material); }

  private:
    Texture *m_texture{};
  };

} // namespace mtEngine
