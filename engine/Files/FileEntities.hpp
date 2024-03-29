#pragma once

#include <any>

#include <Engine/Log.hpp>

#include "Files/File.hpp"
#include "third_party/json/json.hpp"

namespace mtEngine::Files
{
  class FileEntities
  {
    using Json = nlohmann::json;

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

    // camera
    struct Camera;
    struct Dir;
    struct TransformCam;
    using Cameras = std::vector<Camera *>;

    struct Child;

    using Childs = std::vector<std::any>;

    struct Vector3;
    struct Vector4;

    struct Spec
    {
      std::string name;
      std::string author;
      std::string description;
      std::string version;
      EntityItems entities;
      Environment *environment;
      Cameras cameras;
    } spec;

  public:
    FileEntities();
    ~FileEntities();

    static auto Create(const std::filesystem::path &path) -> std::shared_ptr<FileEntities>;
    const Spec &GetSpecification() { return static_cast<Spec &>(spec); };

    struct Vector3
    {
      float x = 0;
      float y = 0;
      float z = 0;
    };

    struct Vector4
    {
      float x = 0;
      float y = 0;
      float z = 0;
      float w = 0;
    };

    struct Entity
    {
      std::string name;
      std::string model;
      Transform *transform;
      Childs childs;
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

    struct Dir
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
      std::string name;
      float strength = 1.0;
      Color color;
      LightDirection direction;
      Transform *transform;
    };

    struct TransformCam
    {
      Vector3 translation;
      Vector3 dir;
    };

    struct Camera
    {
      std::string name;
      TransformCam transform;
      float speed;
      float sensitivity;
      float nearPlane;
      float farPlane;
      float fov;
    };

    struct Child
    {
      std::string link;
    };

  private:
    std::string _buffer;
    Json _jsonParser;
    Json _validJson;

    std::string LoadFromFile(const std::filesystem::path &path) const;
    void CreateSpec();
    void CleanSpec();

  private:
    auto ParseCameras(const Json::array_t *json) -> void;
    auto ParseEntities(const Json::array_t *json) -> void;
    auto ParseEnvironment(const Json::object_t *json) -> void;
    auto ParseChilds(const Json::array_t *json, int idx) -> void;

    auto SearchInEntities(const std::string &name) -> const Entity *;
    auto SearchInCameras(const std::string &name) -> const Camera *;
  };
} // namespace mtEngine::Files
