#pragma once

#include <Engine/Log.hpp>

#include "Files/File.hpp"
#include "third_party/json/json.hpp"

namespace mtEngine::Files
{
  class FileEntities
  {
  public:
    // entity
    struct Entity;
    using EntityItems = std::vector<Entity>;
    struct Transform;
    struct Rotation;
    struct Scale;
    struct Translation;
    // environment
    struct Environment;
    struct Light;
    using Lights = std::vector<Light *>;
    struct LightDirection;
    struct Color;
    struct Skybox;
    struct SkyboxFaces;

    struct Spec
    {
      std::string name;
      std::string author;
      std::string description;
      std::string version;
      EntityItems entities;
      Environment *environment;
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
    };

    struct Rotation
    {
      float x = 0;
      float y = 0;
      float z = 0;
      float w = 1;
    };

    struct Scale
    {
      float x = 1;
      float y = 1;
      float z = 1;
    };

    struct Translation
    {
      float x = 0;
      float y = 0;
      float z = 0;
    };

    struct SkyboxFaces
    {
      std::string positiveX;
      std::string negativeX;
      std::string positiveY;
      std::string negativeY;
      std::string positiveZ;
      std::string negativeZ;
    };

    struct Skybox
    {
      int size;
      SkyboxFaces faces;
    };

    struct Environment
    {
      Lights lights;
      Skybox skybox;
    };

    struct LightDirection
    {
      float x = 0;
      float y = 0;
      float z = 0;
    };

    struct Color
    {
      float r = 0.0f;
      float g = 0.0f;
      float b = 0.0f;
    };

    struct Light
    {
      int size;
      std::string type;
      float strength = 1.0;
      Color color;
      LightDirection direction;
      Transform *transform;
    };

  private:
    std::string _buffer;
    nlohmann::json _jsonParser;

    Lights m_lights;

    std::string LoadFromFile(const std::filesystem::path &path) const;
    void CreateSpec();
    void CleanSpec();
  };
} // namespace mtEngine::Files
