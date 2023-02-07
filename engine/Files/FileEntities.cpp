#include "FileEntities.hpp"

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

  void FileEntities::CreateSpec()
  {
    try
    {
      auto json = _jsonParser.parse(_buffer);
      if (json.contains("name"))
      {
        spec.name = json["name"];
      }
      if (json.contains("author"))
      {
        spec.author = json["author"];
      }
      if (json.contains("description"))
      {
        spec.description = json["description"];
      }
      if (json.contains("version"))
      {
        spec.version = json["version"];
      }

      // entities
      auto ent = json["entities"];
      auto ent_json = ent.get<nlohmann::json::array_t *>();
      for (const auto &p : *ent_json)
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
          entity.transform = s_transform;
        }
        spec.entities.push_back(entity);
      }

      // environment
      auto env = json["environment"];
      auto env_json = env.get<nlohmann::json::object_t *>();
      Environment *_e = new Environment();
      if (env_json->find("lights") != env_json->end())
      {
        auto lights_json = env_json->at("lights");
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
          m_lights.push_back(_l);
        }
        _e->lights = m_lights;
      }

      if (env_json->find("skybox") != env_json->end())
      {
        auto skybox_json = env_json->at("skybox");
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

      ParseCameras(&json);
    }
    catch (nlohmann::json::parse_error &e)
    {
      PLOGE << e.what();
    }
  }

  std::string FileEntities::LoadFromFile(const std::filesystem::path &path) const
  {
    auto file = new File();
    file->Load(path);
    auto buf = file->GetBuffer();
    file = nullptr;

    return buf;
  }

  void FileEntities::CleanSpec()
  {
    spec.author.clear();
    spec.description.clear();
    spec.entities.clear();
    spec.environment->lights.clear();
  }

  auto FileEntities::ParseCameras(const nlohmann::json *json) -> void
  {
    const auto cameras = json->find("cameras");
    for (const auto &c : *cameras)
    {
      const auto cam = new Camera;
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

      cam->transform = transform;

      m_cameras.push_back(cam);
    }

    spec.cameras = m_cameras;
  }
} // namespace mtEngine::Files
