#include "SceneStructure.hpp"
#include <GL/glew.h>

namespace mtEngine {
  SceneStructure::SceneStructure() { };

  Entity *SceneStructure::GetEntity(const std::string &name) const
  {
    for (auto &object : objects) {
      if (object->GetName() == name) {
        return object.get();
      }
    }

    return nullptr;
  }

  Entity *SceneStructure::CreateEntity()
  {
    return objects.emplace_back(std::make_unique<Entity>()).get();
  }

  void SceneStructure::Add(Entity *object) { objects.emplace_back(object); }

  void SceneStructure::Add(std::unique_ptr<Entity> object)
  {
    objects.emplace_back(std::move(object));
  }

  void SceneStructure::Remove(Entity *object)
  {
    objects.erase(std::remove_if(objects.begin(), objects.end(), [object](std::unique_ptr<Entity> &e) {return e.get() == object; }), objects.end());
  }

  void SceneStructure::Move(Entity *object, SceneStructure &structure)
  {
    for (auto it = --objects.end(); it != objects.begin(); --it) {
      if ((*it).get() != object) {
        continue;
      }
      structure.Add(std::move(*it));
      objects.erase(it);
    }
  }

  void SceneStructure::Clear() { objects.clear(); }

  void SceneStructure::Update()
  {
    glClear(GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    for (auto it = objects.begin(); it != objects.end();) {
      if ((*it)->IsRemoved()) {
        it = objects.erase(it);
        continue;
      }

      (*it)->Update();
      ++it;
    }
  }

  bool SceneStructure::Contains(Entity *object)
  {
    for (const auto &object2 : objects) {
      if (object2.get() == object) {
        return true;
      }
    }

    return false;
  }

  std::vector<Entity *> SceneStructure::QueryAll()
  {
    std::vector<Entity *> entities;

    for (const auto &object : objects) {
      if (object->IsRemoved()) continue;

      auto model = object.get()->GetName();
      entities.emplace_back(object.get());
    }

    return entities;
  }
} // namespace mtEngine
