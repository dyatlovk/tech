#pragma once

#include "Graphics/Shader.hpp"
#include "Material.hpp"
#include "Models/Mesh.hpp"
#include "Resources/Resource.hpp"
#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
  class Model : public Resource
  {
  public:
    Model() = default;
    Model(const Shader *shader, const Mesh *mesh, const Material *material);

    static auto Create(const std::string &name, const Shader *shader, const Mesh *mesh, const Material *material)
        -> std::shared_ptr<Model>;

    void Draw();

    [[nodiscard]] auto GetTypeIndex() const -> std::type_index override { return typeid(Model); }

  private:
    Mesh *mesh{};
    Shader *shader{};
    Material *material{};
  };
} // namespace mtEngine
