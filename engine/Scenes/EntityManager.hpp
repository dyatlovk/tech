#pragma once

#include <filesystem>
#include <memory>

#include "Files/FileEntities.hpp"
namespace mtEngine
{
  class EntityManager
  {
  public:
    EntityManager();
    ~EntityManager();

    static auto CreateFromFile(const std::filesystem::path &path) -> std::shared_ptr<EntityManager>;

  private:
    const Files::FileEntities::Spec &LoadSpecification(const std::filesystem::path &path);
    Files::FileEntities::Spec _spec;

  private:
      void CreatEntities(const Files::FileEntities::Spec &spec);
  };
} // namespace mtEngine
