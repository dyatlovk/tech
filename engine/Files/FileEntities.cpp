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
  }
} // namespace mtEngine::Files
