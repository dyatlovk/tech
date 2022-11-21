#pragma once

#include <Engine/Log.hpp>

#include "Files/File.hpp"
#include "third_party/json/json.hpp"

namespace mtEngine::Files
{
  class FileEntities
  {
  public:
    struct Entity;
    using EntityItems = std::vector<Entity>;
    struct Transform;
    struct Rotation;
    struct Scale;
    struct Translation;
    struct Spec
    {
      std::string name;
      std::string author;
      std::string description;
      std::string version;
      EntityItems entities;
    } spec;

  public:
    FileEntities();
    ~FileEntities();

    static auto Create(const std::filesystem::path &path) -> std::shared_ptr<FileEntities>;
    const Spec &GetSpecification() { return static_cast<Spec &>(spec); };

    struct Entity
    {
      std::string model;
      Transform *transform;
    };

    struct Transform
    {
      Translation *translation;
      Rotation *rotation;
      Scale *scale;
    } _transform;

    struct Rotation
    {
      float x = 0;
      float y = 0;
      float z = 0;
      float w = 1;
    } _rotation;

    struct Scale
    {
      float x = 1;
      float y = 1;
      float z = 1;
    } _scale;

    struct Translation
    {
      float x = 0;
      float y = 0;
      float z = 0;
    } _translation;

  private:
    std::string _buffer;
    nlohmann::json _jsonParser;

    std::string LoadFromFile(const std::filesystem::path &path) const;
    void CreateSpec();
    void CleanSpec();
  };
} // namespace mtEngine::Files
