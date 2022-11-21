#pragma once

#include <vector>

#include "Entity.hpp"

namespace mtEngine
{
  class SceneStructure : public NonCopyable
  {
  public:
    SceneStructure();

    Entity *GetEntity(const std::string &name) const;

    Entity *CreateEntity();

    void Add(Entity *object);

    void Add(std::unique_ptr<Entity> object);

    void Remove(Entity *object);

    void Move(Entity *object, SceneStructure &structure);

    void Clear();

    void Update();

    bool Contains(Entity *object);

    uint32_t GetSize() const { return static_cast<uint32_t>(objects.size()); }

    std::vector<Entity *> QueryAll();

  private:
    std::vector<std::unique_ptr<Entity>> objects;
  };
} // namespace mtEngine
