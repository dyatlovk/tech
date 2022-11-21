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
          if (transform.contains("translation"))
          {
            _translation.x = transform.at("translation")[0];
            _translation.y = transform.at("translation")[1];
            _translation.z = transform.at("translation")[2];
            _transform.translation = &_translation;
          }
          if (transform.contains("rotation"))
          {
            _rotation.x = transform.at("rotation")[0];
            _rotation.y = transform.at("rotation")[1];
            _rotation.z = transform.at("rotation")[2];
            _rotation.w = transform.at("rotation")[3];
            _transform.rotation = &_rotation;
          }
          if (transform.contains("scale"))
          {
            _scale.x = transform.at("scale")[0];
            _scale.y = transform.at("scale")[1];
            _scale.z = transform.at("scale")[2];
            _transform.scale = &_scale;
          }
          entity.transform = &_transform;
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
