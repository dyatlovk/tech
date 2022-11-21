#pragma once

#include <vector>

#include "Component.hpp"
#include "Utils/NonCopyable.hpp"

namespace mtEngine
{
  class Entity : public NonCopyable
  {
  public:
    Entity(){};

    void Update();

    const std::string &GetName() const { return name; }

    void SetName(const std::string &name) { this->name = name; }

    bool IsRemoved() const { return removed; }

    void SetRemoved(bool removed) { this->removed = removed; }

    const std::vector<std::unique_ptr<Component>> *GetComponents() const { return &components; }

    uint32_t GetComponentCount() const { return static_cast<uint32_t>(components.size()); }

    Component *AddComponent(std::unique_ptr<Component> &&component);

    template<typename T, typename... Args>
    T *AddComponent(Args &&...args)
    {
      return dynamic_cast<T *>(AddComponent(std::make_unique<T>(std::forward<Args>(args)...)));
    }

    void RemoveComponent(Component *component);

    bool SetVisible(bool &value)
    {
      isVisible = value;
      return value;
    };

    bool SetVisible(int value)
    {
      bool res = false;
      if (value == 0)
      {
        res = false;
      }
      else
      {
        res = true;
      }
      isVisible = res;
      return res;
    };

    bool IsVisible() { return isVisible; };

    bool SetRenderWireframe(bool &value)
    {
      renderWireframe = value;
      return renderWireframe;
    };

    bool isRenderWireframe() { return renderWireframe; };

    template<typename T>
    void RemoveComponent()
    {
      for (auto it = components.begin(); it != components.end(); ++it)
      {
        auto casted = dynamic_cast<T *>((*it).get());

        if (casted)
        {
          (*it)->SetEntity(nullptr);
          components.erase(it);
        }
      }
    }

    template<typename T>
    T *GetComponent(bool allowDisabled = false) const
    {
      T *alternative = nullptr;

      for (const auto &component : components)
      {
        auto casted = dynamic_cast<T *>(component.get());

        if (casted)
        {
          if (allowDisabled && !component->IsEnabled())
          {
            alternative = casted;
            continue;
          }

          return casted;
        }
      }

      return alternative;
    }

    template<typename T>
    std::vector<T *> GetComponents(bool allowDisabled = false) const
    {
      std::vector<T *> components;

      for (const auto &component : this->components)
      {
        auto casted = dynamic_cast<T *>(component.get());

        if (casted)
        {
          if (allowDisabled && !component->IsEnabled())
          {
            components.emplace_back(casted);
            continue;
          }

          components.emplace_back(casted);
        }
      }

      return components;
    }

  private:
    std::string name;
    bool removed = false;
    bool isVisible = true;
    bool renderWireframe = false;
    std::vector<std::unique_ptr<Component>> components;
  };
} // namespace mtEngine
