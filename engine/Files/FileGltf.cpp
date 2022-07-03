#include "FileGltf.hpp"

#include "Files/File.hpp"

namespace mtEngine
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
    auto json = _jsonParser.parse(_buffer);

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
  }

  void FileGltf::CleanSpec()
  {
    spec.nodes = nullptr;
    spec.meshes = nullptr;
    spec.accessors = nullptr;
    spec.buffers = nullptr;
    spec.bufferViews = nullptr;
  }
} // namespace mtEngine
