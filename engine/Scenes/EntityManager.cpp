#include "EntityManager.hpp"

#include "Light/Light.hpp"
#include "Models/Model.hpp"
#include "Scenes/Components/Transform.hpp"
#include "Scenes/Scenes.hpp"
#include "third_party/glm/ext/vector_float3.hpp"

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

  auto EntityManager::Remove(const std::string &name) -> void
  {
    auto _e = mtEngine::Scenes::Get()->GetStructure()->GetEntity(name);
    if (!_e) return;
    auto model = _e->GetComponent<Model>();
    mtEngine::Scenes::Get()->GetStructure()->Remove(_e);
    _e = nullptr;
    PLOGD << "entity "<< name << " removed";
  }

  auto EntityManager::Add(const std::string &path, const std::string &name) -> void
  {
    auto _e = mtEngine::Scenes::Get()->GetStructure()->CreateEntity();
    _e->SetName(name);
    _e->AddComponent<Model>(Model::Create(path));
    _e->AddComponent<Transform>(glm::vec3(0.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    PLOGD << "entity: " << name << " added";
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
      _e->SetName(e.name);
      _e->AddComponent<Model>(Model::Create(p + e.model));

      const auto translate = glm::vec3(e.transform->translation->x, e.transform->translation->y, e.transform->translation->z);
      const auto rotation  = glm::vec4(e.transform->rotation->x, e.transform->rotation->y, e.transform->rotation->z, e.transform->rotation->w);
      const auto scale     = glm::vec3(e.transform->scale->x, e.transform->scale->y, e.transform->scale->z);
      _e->AddComponent<Transform>(translate, rotation, scale);
    }

    const auto env = spec.environment;
    const auto lights = env->lights;
    for (const auto &l : lights)
    {
      auto _e = mtEngine::Scenes::Get()->GetStructure()->CreateEntity();
      _e->SetName("Sun");

      const auto translate = glm::vec3(l->transform->translation->x, l->transform->translation->y, l->transform->translation->z);
      const auto rotation  = glm::vec4(l->transform->rotation->x, l->transform->rotation->y, l->transform->rotation->z, l->transform->rotation->w);
      const auto scale     = glm::vec3(l->transform->scale->x, l->transform->scale->y, l->transform->scale->z);
      _e->AddComponent<Transform>(translate, rotation, scale);

      const auto _dir   = glm::vec3(l->direction.x, l->direction.y, l->direction.z);
      const auto _color = glm::vec3(l->color.r, l->color.g, l->color.b);
      _e->AddComponent<Light>(_color, l->size, l->strength, _dir);
    }
  }
} // namespace mtEngine
