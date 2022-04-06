#include "ResourcesManager.hpp"

namespace mtEngine
{
  ResourcesManager::ResourcesManager() { PLOGD; };

  void ResourcesManager::Update() { return; }

  std::shared_ptr<Resource> ResourcesManager::find(const std::string &name) const
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
        return resource;
      }
    }

    return nullptr;
  }

  void ResourcesManager::add(
      const std::string &name, const std::shared_ptr<Resource> &value)
  {
    std::size_t hash = std::hash<std::string>{}(name);
    if (find(name))
    {
      return;
    }
    resources[hash].emplace(name, value);
  }

  void ResourcesManager::remove(const std::string &name)
  {
    std::size_t hash = std::hash<std::string>{}(name);
    auto _res = this->resources[hash];
    PLOGD << name;
    for (auto it = _res.begin(); it != _res.end(); ++it)
    {
      if (it->first == name)
        _res.erase(it);
    }
  }

  void ResourcesManager::replace(
      const std::string &name, const std::shared_ptr<Resource> &value)
  {
    std::size_t hash = std::hash<std::string>{}(name);
    auto it = this->resources.find(hash);
    auto res = it->second.at(name);
    it->second.at(name) = value;
  }

  ResourcesManager::ResourcesContainer_t ResourcesManager::GetAll() const
  {
    return resources;
  }
} // namespace mtEngine
