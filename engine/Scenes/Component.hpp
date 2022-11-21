#pragma once

#include <Utils/ComponentsFactory.hpp>
#include <iostream>

namespace mtEngine
{
  class Entity;
  class Component : public ComponentsFactory<Component>
  {
    friend class Entity;

  public:
    Component() = default;

    virtual void Start() {}
    virtual void Update() {}

    bool IsEnabled() const { return enabled; };
    void SetEnabled(bool enable) { this->enabled = enable; }

    bool IsRemoved() const { return removed; }
    void SetRemoved(bool removed) { this->removed = removed; }

    Entity *GetEntity() const { return entity; }

    void SetEntity(Entity *entity) { this->entity = entity; }

  private:
    bool started = false;
    bool enabled = true;
    bool removed = false;
    Entity *entity = nullptr;
  };
} // namespace mtEngine
