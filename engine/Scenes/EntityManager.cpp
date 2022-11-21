#include "EntityManager.hpp"

#include "Models/Model.hpp"
#include "Scenes/Components/Transform.hpp"
#include "Scenes/Scenes.hpp"

namespace mtEngine
{
  EntityManager::EntityManager() = default;
  EntityManager::~EntityManager() = default;

  auto EntityManager::CreateFromFile(const std::filesystem::path &path) -> std::shared_ptr<EntityManager>
  {
    auto inst = std::make_shared<EntityManager>();
    auto spec = Files::FileEntities::Create(path);
    inst->CreatEntities(spec->GetSpecification());

    return inst;
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  void EntityManager::CreatEntities(const Files::FileEntities::Spec &spec)
  {
    const std::string p(RESOURCES);
    const auto ents = spec.entities;
    for (const auto &e : ents)
    {
      auto _e = mtEngine::Scenes::Get()->GetStructure()->CreateEntity();
      _e->AddComponent<Model>(Model::Create(p + e.model));
      const auto translate =
          glm::vec3(e.transform->translation->x, e.transform->translation->y, e.transform->translation->z);
      const auto rotation = glm::vec4(
          e.transform->rotation->x, e.transform->rotation->y, e.transform->rotation->z, e.transform->rotation->w);
      const auto scale = glm::vec3(e.transform->scale->x, e.transform->scale->y, e.transform->scale->z);
      _e->AddComponent<Transform>(translate, rotation, scale);
    }
  }
} // namespace mtEngine
