#include "Mesh.hpp"

#include <Files/File.hpp>

namespace mtEngine
{

  Mesh::~Mesh() { CleanBuffers(); }

  std::shared_ptr<Mesh> Mesh::Create(
      const std::string &name, const std::filesystem::path &path)
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Mesh>(name))
      return resource;

    const std::string p(RESOURCES);
    auto resource = std::make_shared<Mesh>();
    resource->LoadSpecification(path);
    resource->LoadGeometry();
    resource->SetupPrimitives();

    mgr->add(name, resource);

    return resource;
  }

  void Mesh::SetupPrimitives()
  {
    auto primitives = gltfSpec.meshes->GetItems().at(0).primitives;
    auto accessors = gltfSpec.accessors->GetItems();
    for(const auto &primitive : primitives)
    {
      GLBuffer buf;
      glGenVertexArrays(1, &buf.vao);
      glGenBuffers(1, &buf.vbo);
      glGenBuffers(1, &buf.ebo);
      glBindVertexArray(buf.vao);
      glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
      const auto accessorsPrimitive = FindPrimitiveAccessors(primitive);
      const auto verticesSize = PrimitiveVerticesSize(accessorsPrimitive);
      const auto indecesSize = PrimitiveIndecesSize(primitive);
      const auto verticesPosition = primitive.attr.position;
      const auto indicesPosition = *primitive.indices;
      const auto indicesOffset = PrimitiveIndecesOffset(indicesPosition);
      glBufferData(GL_ARRAY_BUFFER, verticesSize, BufferOffset(verticesPosition), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecesSize, BufferOffset(indicesOffset), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      buf.indecesCount = accessors.at(indicesPosition).count;

      glBindVertexArray(0);
      _glBuffers.push_back(buf);
    }
  }

  void Mesh::CleanBuffers()
  {
   for(const auto &buf : _glBuffers)
   {
      glDeleteVertexArrays(1, &buf.vao);
      glDeleteBuffers(1, &buf.vbo);
      glDeleteBuffers(1, &buf.ebo);
   }
  }

  void Mesh::Draw()
  {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for(const auto &buf : _glBuffers)
    {
      glBindVertexArray(buf.vao);
      glDrawElements(GL_TRIANGLES, buf.indecesCount, GL_UNSIGNED_SHORT, nullptr);
      glBindVertexArray(0);
    }
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  void Mesh::LoadSpecification(const std::filesystem::path &path)
  {
    auto gltf = FileGltf::Create(path);
    gltfSpec = gltf->GetSpec();
  }

  void Mesh::LoadGeometry()
  {
    const std::string p(RESOURCES);
    if (!gltfSpec.buffers)
    {
      PLOGE << "gltf specification not loaded";
      return;
    }
    auto binFilePath = *gltfSpec.buffers->GetItems().at(0).uri;
    auto binPath = p + "/Game/models/yard/" + binFilePath;
    auto binFile = new File(binPath);
    _fileBuffer = binFile->GetBuffer();
    delete binFile;
  }

  const char *Mesh::BufferOffset(const unsigned int &bytes)
  {
    auto buffer = &_fileBuffer.at(0) + bytes;

    return buffer;
  }

  std::vector<Accessors::Item> Mesh::FindPrimitiveAccessors(const Meshes::PrimitiveItem &item)
  {
    auto accessors = gltfSpec.accessors->GetItems();
    int idFrom = item.attr.position;
    int idTo = *item.indices;

    auto it = accessors.begin() + idFrom;
    auto itEnd = accessors.begin() + idTo;

    std::vector<Accessors::Item> result;

    for (; it != itEnd; it++)
    {
      result.push_back(*it);
    }

    return result;
  }

  unsigned int Mesh::PrimitiveVerticesSize(std::vector<Accessors::Item> accessors)
  {
    unsigned int bytes = 0;
    const auto buffers = gltfSpec.bufferViews->GetItems();
    for (const auto &accessor : accessors)
    {
      const auto buffer = buffers.at(*accessor.bufferView);
      bytes += buffer.byteLength;
    }
    return bytes;
  }

  unsigned int Mesh::PrimitiveIndecesSize(const Meshes::PrimitiveItem &item)
  {
    const auto buffers = gltfSpec.bufferViews->GetItems();
    unsigned int bytes = buffers.at(*item.indices).byteLength;

    return bytes;
  }

  unsigned int Mesh::PrimitiveIndecesOffset(const unsigned int position)
  {
    const auto buffers = gltfSpec.bufferViews->GetItems();
    unsigned int bytes = *buffers.at(position).byteOffset;

    return bytes;
  }
} // namespace mtEngine
