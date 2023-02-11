#include "FileEntities.hpp"

#include <type_traits>

#include "Utils/String.hpp"

namespace mtEngine::Files
{
  FileEntities::FileEntities() = default;

  FileEntities::~FileEntities()
  {
    CleanSpec();
  }

  auto FileEntities::Create(const std::filesystem::path &path) -> std::shared_ptr<FileEntities>
  {
    const auto instance = std::make_shared<FileEntities>();
    instance->_buffer = instance->LoadFromFile(path);
    instance->CreateSpec();

    return instance;
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  // ---------------------------------------------------------------------------
  void FileEntities::CreateSpec()
  {
    const auto isValid = _jsonParser.accept(_buffer);
    if (!isValid)
    {
      PLOGD << "scene file is not valid";
      return;
    }

    _validJson = _jsonParser.parse(_buffer);
    if (_validJson.contains("name"))
    {
      spec.name = _validJson["name"];
    }
    if (_validJson.contains("author"))
    {
      spec.author = _validJson["author"];
    }
    if (_validJson.contains("description"))
    {
      spec.description = _validJson["description"];
    }
    if (_validJson.contains("version"))
    {
      spec.version = _validJson["version"];
    }

    // cameras
    auto cam = _validJson["cameras"];
    const auto camJson = cam.get<Json::array_t *>();
    ParseCameras(camJson);

    // environment
    auto env = _validJson["environment"];
    auto env_json = env.get<Json::object_t *>();
    ParseEnvironment(env_json);

    // entities
    auto ent = _validJson["entities"];
    auto ent_json = ent.get<Json::array_t *>();
    ParseEntities(ent_json);
  }

  // ---------------------------------------------------------------------------
  std::string FileEntities::LoadFromFile(const std::filesystem::path &path) const
  {
    auto file = new File();
    file->Load(path);
    auto buf = file->GetBuffer();
    file = nullptr;
    delete file;

    return buf;
  }

  // ---------------------------------------------------------------------------
  void FileEntities::CleanSpec()
  {
    spec.author.clear();
    spec.description.clear();
    spec.entities.clear();
    spec.environment->lights.clear();
    spec.cameras.clear();
  }

  // ---------------------------------------------------------------------------
  auto FileEntities::ParseCameras(const Json::array_t *json) -> void
  {
    for (const auto &c : *json)
    {
      Camera *cam = new Camera;
      const auto name = c["name"];
      cam->name = name;
      TransformCam transform;
      const auto tr = c["transform"];

      Vector3 translation;
      auto _translate = tr.at("translation");
      translation.x = (float)_translate.at(0);
      translation.y = (float)_translate.at(1);
      translation.z = (float)_translate.at(2);
      transform.translation = translation;

      Vector3 dir;
      auto _dir = tr.at("dir");
      dir.x = (float)_dir.at(0);
      dir.y = (float)_dir.at(1);
      dir.z = (float)_dir.at(2);
      transform.dir = dir;

      cam->speed = (float)c.at("speed");
      cam->sensitivity = (float)c.at("sensitivity");
      cam->nearPlane = (float)c.at("nearPlane");
      cam->farPlane = (float)c.at("farPlane");
      cam->fov = (float)c.at("fov");

      cam->transform = transform;

      spec.cameras.push_back(cam);
      cam = nullptr;
      delete cam;
    }
  }

  // ---------------------------------------------------------------------------
  auto FileEntities::ParseEntities(const Json::array_t *json) -> void
  {
    int idx = 0;
    for (const auto &p : *json)
    {
      Entity entity;
      if (p.contains("name"))
      {
        entity.name = std::string(p["name"]);
      }
      if (p.contains("model"))
      {
        entity.model = std::string(p["model"]);
      }
      // transform
      if (p.contains("transform"))
      {
        const auto transform = p.at("transform");
        Transform *s_transform = new Transform();
        if (transform.contains("translation"))
        {
          Translation *s_translation = new Translation();
          s_translation->x = (float)transform.at("translation")[0];
          s_translation->y = (float)transform.at("translation")[1];
          s_translation->z = (float)transform.at("translation")[2];
          s_transform->translation = s_translation;
          s_translation = nullptr;
          delete s_translation;
        }
        if (transform.contains("rotation"))
        {
          Rotation *s_rotation = new Rotation();
          s_rotation->x = (float)transform.at("rotation")[0];
          s_rotation->y = (float)transform.at("rotation")[1];
          s_rotation->z = (float)transform.at("rotation")[2];
          s_rotation->w = (float)transform.at("rotation")[3];
          s_transform->rotation = s_rotation;
          s_rotation = nullptr;
          delete s_rotation;
        }
        if (transform.contains("scale"))
        {
          Scale *s_scale = new Scale();
          s_scale->x = (float)transform.at("scale")[0];
          s_scale->y = (float)transform.at("scale")[1];
          s_scale->z = (float)transform.at("scale")[2];
          s_transform->scale = s_scale;
          s_scale = nullptr;
          delete s_scale;
        }
        entity.transform = s_transform;
        s_transform = nullptr;
        delete s_transform;
      }
      spec.entities.push_back(entity);

      if (p.contains("childs"))
      {
        auto childs = p.at("childs");
        auto chJson = childs.get<Json::array_t *>();
        ParseChilds(chJson, idx);
      }
      idx++;
    }
  }

  // ---------------------------------------------------------------------------
  auto FileEntities::ParseEnvironment(const Json::object_t *json) -> void
  {
    Environment *_e = new Environment();
    if (json->find("lights") != json->end())
    {
      auto lights_json = json->at("lights");
      for (const auto &l : lights_json)
      {
        auto _l = new Light();
        _l->size = (int)l["size"];
        _l->type = std::string(l["type"]);
        if (l.contains("transform"))
        {
          const auto transform = l.at("transform");
          Transform *s_transform = new Transform();
          if (transform.contains("translation"))
          {
            Translation *s_translation = new Translation();
            s_translation->x = (float)transform.at("translation")[0];
            s_translation->y = (float)transform.at("translation")[1];
            s_translation->z = (float)transform.at("translation")[2];
            s_transform->translation = s_translation;
          }
          if (transform.contains("rotation"))
          {
            Rotation *s_rotation = new Rotation();
            s_rotation->x = (float)transform.at("rotation")[0];
            s_rotation->y = (float)transform.at("rotation")[1];
            s_rotation->z = (float)transform.at("rotation")[2];
            s_rotation->w = (float)transform.at("rotation")[3];
            s_transform->rotation = s_rotation;
          }
          if (transform.contains("scale"))
          {
            Scale *s_scale = new Scale();
            s_scale->x = (float)transform.at("scale")[0];
            s_scale->y = (float)transform.at("scale")[1];
            s_scale->z = (float)transform.at("scale")[2];
            s_transform->scale = s_scale;
          }
          _l->transform = s_transform;
        }
        if (l.contains("direction"))
        {
          const auto light_dir_json = l["direction"];
          LightDirection s_lightDir;
          s_lightDir.x = (float)light_dir_json[0];
          s_lightDir.y = (float)light_dir_json[1];
          s_lightDir.z = (float)light_dir_json[2];
          _l->direction = s_lightDir;
        }
        if (l.contains("color"))
        {
          const auto light_color_json = l["color"];
          Color s_light_color;
          s_light_color.r = (float)light_color_json[0];
          s_light_color.g = (float)light_color_json[1];
          s_light_color.b = (float)light_color_json[2];
          _l->color = s_light_color;
        }
        if (l.contains("strength"))
        {
          _l->strength = (float)l["strength"];
        }
        _e->lights.push_back(_l);
        _l = nullptr;
        delete _l;
      }
    }

    if (json->find("skybox") != json->end())
    {
      auto skybox_json = json->at("skybox");
      Skybox s_skybox;
      if (skybox_json.contains("size"))
      {
        s_skybox.size = skybox_json["size"];
      }
      if (skybox_json.contains("textures"))
      {
        SkyboxFaces s_faces;
        auto skybox_faces = skybox_json["textures"];
        s_faces.positiveX = skybox_faces["positiveX"];
        s_faces.negativeX = skybox_faces["negativeX"];
        s_faces.positiveY = skybox_faces["positiveY"];
        s_faces.negativeY = skybox_faces["negativeY"];
        s_faces.positiveZ = skybox_faces["positiveZ"];
        s_faces.negativeZ = skybox_faces["negativeZ"];
        s_skybox.faces = s_faces;
      }
      _e->skybox = s_skybox;
    }

    spec.environment = _e;
    _e = nullptr;
    delete _e;
  }

  auto FileEntities::ParseChilds(const Json::array_t *json, int idx) -> void
  {
    for (const auto &link : *json)
    {
      const auto foundEntity = SearchInEntities(link);
      if (foundEntity)
      {
        spec.entities.at(idx).childs.push_back(foundEntity);
      }

      const auto foundCams = SearchInCameras(link);
      if (foundCams)
      {
        spec.entities.at(idx).childs.push_back(foundCams);
      }
    }
  }

  // ---------------------------------------------------------------------------
  auto FileEntities::SearchInEntities(const std::string &name) -> const Entity *
  {
    const auto tokens = mtEngine::String::Split(name, ".");
    if (tokens.size() == 0)
    {
      return nullptr;
    }
    const auto section = tokens.at(0);
    const auto findName = tokens.at(1);

    if (section == "entities")
    {
      for (const auto &entity : spec.entities)
      {
        if (entity.name.compare(findName) == 0)
        {
          return &entity;
        }
      }
    }

    return nullptr;
  }

  // ---------------------------------------------------------------------------
  auto FileEntities::SearchInCameras(const std::string &name) -> const Camera *
  {
    const auto tokens = mtEngine::String::Split(name, ".");
    if (tokens.size() == 0)
    {
      return nullptr;
    }
    const auto section = tokens.at(0);
    const auto findName = tokens.at(1);

    if (section == "cameras")
    {
      for (const auto &cam : spec.cameras)
      {
        if (cam->name.compare(findName) == 0)
        {
          return cam;
        }
      }
    }

    return nullptr;
  }
} // namespace mtEngine::Files
