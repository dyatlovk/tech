#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Maths/Vectors/Vector3d.hpp"
#include "third_party/json/json.hpp"

namespace Game::Client
{
  constexpr static std::string_view DEFAULT_TYPE = "Sun";
  using json = nlohmann::json;

  struct Transform;
  struct Translate;
  struct Scale;
  struct Rotate;
  struct Camera;
  struct Entity;
  struct SceneInfo;
  struct Environment;
  struct Light;
  struct Object;

  struct Entity
  {
    std::string name;
    Transform *transform = nullptr;
  };

  struct SceneInfo
  {
    std::vector<Entity *> entities;
    Environment *environment = nullptr;
  };

  struct ObjectInfo
  {
    Entity entity;
  };

  struct Environment
  {
    std::vector<Light *> lights;
  };

  struct Light
  {
    int size = 5;
    std::string type = std::string(DEFAULT_TYPE);
    mtEngine::mtVec3f *color = nullptr;
    mtEngine::mtVec3f *direction = nullptr;
    Transform *transform = nullptr;
    float strength = 1;
  };

  struct Translate
  {
    float x;
    float y;
    float z;
  };

  struct Rotate
  {
    float x;
    float y;
    float z;
    float w;
  };

  struct Scale
  {
    float x;
    float y;
    float z;
  };

  struct Transform
  {
    Translate *translate;
    Rotate *rotate;
    Scale *scale;
  };

  struct Camera
  {
    Transform *transform;
    Transform *dir;
  };

  inline auto MakeScene(const json *json) -> std::unique_ptr<SceneInfo> const
  {
    auto s = std::make_unique<SceneInfo>();
    const auto scene = json->find("scene_info");
    if (scene == json->end())
    {
      std::cout << "scene_info not found" << std::endl;
      return s;
    }
    const auto entities = scene->find("entities");
    for (const auto &e : *entities)
    {
      auto entity = new Entity;
      const auto translate = new Translate;
      const auto transform = new Transform;
      const auto name = std::string(e["name"]);
      entity->name = name;
      const auto tr = e["transform"];
      const auto trans = tr["translation"];
      translate->x = (float)trans[0];
      translate->y = (float)trans[1];
      translate->z = (float)trans[2];
      transform->translate = translate;
      entity->transform = transform;
      s->entities.emplace_back(entity);
    }

    const auto env = scene->find("environment");
    if (env == scene->end())
    {
      std::cout << "scene env not present" << std::endl;
      return s;
    }
    const auto lights = env->find("lights");
    for (const auto &l : *lights)
    {
      auto _env = new Environment;
      auto _light = new Light;
      auto _color = new mtEngine::mtVec3f;
      const auto type = std::string(l["type"]);
      _light->type = type;
      _color->x = (float)l["color"][0];
      _color->y = (float)l["color"][1];
      _color->z = (float)l["color"][2];
      _light->size = (int)l["size"];
      _light->color = _color;
      _light->strength = (float)l["strength"];
      _env->lights.push_back(_light);
      s->environment = _env;
    }
    return s;
  }

  inline auto MakeObject(const json *json) -> std::unique_ptr<ObjectInfo>
  {
    auto s = std::make_unique<ObjectInfo>();
    const auto object = json->find("object_info");

    if (object == json->end())
    {
      return s;
    }

    auto translate = new Translate;
    auto transform = new Transform;
    auto rotate = new Rotate;
    auto scale = new Scale;
    Entity e;
    const auto name = object->find("name");
    e.name = std::string(*name);
    const auto tr = object->find("transform");
    const auto trans = tr->find("translation");
    const auto rot = tr->find("rotation");
    const auto sc = tr->find("scale");
    translate->x = (float)trans->at(0);
    translate->y = (float)trans->at(1);
    translate->z = (float)trans->at(2);
    transform->translate = translate;
    rotate->x = (float)rot->at(0);
    rotate->y = (float)rot->at(1);
    rotate->z = (float)rot->at(2);
    rotate->w = (float)rot->at(3);
    transform->rotate = rotate;
    scale->x = (float)sc->at(0);
    scale->y = (float)sc->at(1);
    scale->z = (float)sc->at(2);
    transform->scale = scale;
    e.transform = transform;
    s->entity = e;
    return s;
  }

  inline auto serialize(const SceneInfo *scene) -> void {}
} // namespace Game::Client
