#include "Entity.hpp"

#include "Component.hpp"

namespace mtEngine
{
  Component *Entity::AddComponent(std::unique_ptr<Component> &&component)
  {
    if (!component)
      return nullptr;

    component->SetEntity(this);
    return components.emplace_back(std::move(component)).get();
  }

  void Entity::Update()
  {
    if (!isVisible)
      return;

    for (auto it = components.begin(); it != components.end();)
    {
      if ((*it)->IsRemoved())
      {
        it = components.erase(it);
        continue;
      }

      if ((*it)->GetEntity() != this)
        (*it)->SetEntity(this);

      if ((*it)->IsEnabled())
      {
        if (!(*it)->started)
        {
          (*it)->Start();
          (*it)->started = true;
        }

        (*it)->Update();
      }

      ++it;
    }
  }

  void Entity::RemoveComponent(Component *component)
  {
    components.erase(std::remove_if(components.begin(), components.end(),
                         [component](std::unique_ptr<Component> &c) { return c.get() == component; }),
        components.end());
  }
} // namespace mtEngine
