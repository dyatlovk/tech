#include "FileGltf.hpp"

#include "Files/File.hpp"

namespace mtEngine::Files
{
  FileGltf::FileGltf() {}

  FileGltf::~FileGltf() { CleanSpec(); }

  std::shared_ptr<FileGltf> FileGltf::Create(const std::filesystem::path path)
  {
    auto instance = std::make_shared<FileGltf>();
    instance->_buffer = instance->LoadFromFile(path);
    instance->CreateSpec();

    return instance;
  }

  std::string FileGltf::LoadFromFile(const std::filesystem::path path) const
  {
    auto file = new File();
    file->Load(path);
    auto buf = file->GetBuffer();
    file = nullptr;

    return buf;
  }

  void FileGltf::CreateSpec()
  {
    try
    {
      auto json = _jsonParser.parse(_buffer);

      auto scenes = json["scenes"];
      auto sc = scenes.get<nlohmann::json::array_t *>();
      spec.scenes = new Scenes(sc);
      
      auto assets = json["asset"];
      auto as = assets.get<nlohmann::json::object_t *>();
      spec.assets = new Asset(as);

      auto nodes = json["nodes"];
      auto n = nodes.get<nlohmann::json::array_t *>();
      spec.nodes = new Nodes(n);

      auto meshes = json["meshes"];
      auto m = meshes.get<nlohmann::json::array_t *>();
      spec.meshes = new Meshes(m);

      auto accessors = json["accessors"];
      auto a = accessors.get<nlohmann::json::array_t *>();
      spec.accessors = new Accessors(a);

      auto bufViews = json["bufferViews"];
      auto bv = bufViews.get<nlohmann::json::array_t *>();
      spec.bufferViews = new BufferViews(bv);

      auto buf = json["buffers"];
      auto b = buf.get<nlohmann::json::array_t *>();
      spec.buffers = new Buffers(b);

      auto mat = json["materials"];
      auto _mat = mat.get<nlohmann::json::array_t *>();
      spec.materials = new Materials(_mat);

      auto tex = json["textures"];
      auto _tex = mat.get<nlohmann::json::array_t *>();
      spec.textures = new Textures(_tex);

      auto imgs = json["images"];
      auto _imgs = imgs.get<nlohmann::json::array_t *>();
      spec.images = new Images(_imgs);

      if(json.contains("extras"))
      {
        auto extras = json["extras"];
        auto ex = extras.get<nlohmann::json::object_t *>();
        spec.extras = new Extras(ex);
      }
    } catch(nlohmann::json::parse_error& e) {
      PLOGE << e.what();
    }
  }

  void FileGltf::CleanSpec()
  {
    spec.scenes = nullptr;
    spec.assets = nullptr;
    spec.nodes = nullptr;
    spec.meshes = nullptr;
    spec.accessors = nullptr;
    spec.buffers = nullptr;
    spec.bufferViews = nullptr;
    spec.extras = nullptr;
  }
} // namespace mtEngine
