#pragma once

#include "Graphics/Shader.hpp"
#include "Models/Mesh.hpp"
#include "Resources/Resource.hpp"
#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
  class Model : public Resource
  {
  public:
    Model() = default;
    Model(const Shader *shader, const Mesh *mesh);

    static std::shared_ptr<Model> Create(
        const std::string &name, const Shader *shader, const Mesh *mesh);

    void Draw();

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Model);
    }

  private:
    Mesh *mesh;
    Shader *shader;
  };
} // namespace mtEngine
