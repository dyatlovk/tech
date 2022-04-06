#pragma once

#include <memory>
#include <unordered_map>

#include "Engine/Engine.hpp"
#include "Resource.hpp"

namespace mtEngine
{
  class ResourcesManager : public Module::Registrar<ResourcesManager>
  {
    inline static const bool Registered = Register(Stage::Post);

  private:
    typedef std::unordered_map<std::size_t, std::map<std::string, std::shared_ptr<Resource>>> ResourcesContainer_t;

  public:
    ResourcesManager();

    void Update() override;

    std::shared_ptr<Resource> find(const std::string &name) const;

    template<typename T>
    std::shared_ptr<T> find(const std::string &name) const
    {
      std::size_t hash = std::hash<std::string>{}(name);

      if (resources.find(hash) == resources.end())
      {
        return nullptr;
      }

      for (const auto &[key, resource] : resources.at(hash))
      {
        if (key == name)
        {
          return std::dynamic_pointer_cast<T>(resource);
        }
      }

      return nullptr;
    }

    template<typename T>
    ResourcesContainer_t Filter() const
    {
      ResourcesContainer_t _found = {};

      auto resources = GetAll();

      for (const auto &resource : resources)
      {
        for (const auto &res : resource.second)
        {
          if (res.second->GetTypeIndex() == typeid(T))
          {
            _found.emplace(resource);
          }
        }
      }

      return _found;
    }

    void add(const std::string &name, const std::shared_ptr<Resource> &value);

    void remove(const std::string &name);
    void replace(const std::string &name, const std::shared_ptr<Resource> &value);
    ResourcesContainer_t GetAll() const;

  private:
    ResourcesContainer_t resources;
  };
} // namespace mtEngine
