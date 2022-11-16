#include "Model.hpp"

namespace mtEngine
{
  Model::Model(const Shader *shader, const Mesh *mesh, const Material *mat)
  {
    this->mesh = const_cast<Mesh *>(mesh);
    this->shader = const_cast<Shader *>(shader);
    this->material = const_cast<Material *>(mat);
  }

  auto Model::Create(const std::string &name, const Shader *shader, const Mesh *mesh, const Material *material)
      -> std::shared_ptr<Model>
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Model>(name))
      return resource;

    auto resource = std::make_shared<Model>(shader, mesh, material);
    resource->material = const_cast<Material *>(material);
    resource->shader = const_cast<Shader *>(shader);
    resource->mesh = const_cast<Mesh *>(mesh);
    mgr->add(name, resource);

    return resource;
  }

  void Model::Draw()
  {
    if (shader)
      shader->Use();

    if (material)
      material->Draw();

    if (mesh)
      mesh->Draw();
  }
} // namespace mtEngine
