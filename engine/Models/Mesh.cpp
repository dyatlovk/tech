#include "Mesh.hpp"

#include <Files/File.hpp>

#include "Graphics/Shader.hpp"
#include "Maths/Vectors/Matrix4.hpp"
#include "third_party/glm/fwd.hpp"
#include "third_party/glm/gtc/type_ptr.hpp"
#include "third_party/glm/gtx/quaternion.hpp"
#include <Maths/Transformation.hpp>

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
    resource->SetupNodes();

    mgr->add(name, resource);

    return resource;
  }

  void Mesh::SetupNodes()
  {
    auto nodes = gltfSpec.nodes->GetItems();
    int id = 0;
    for(const auto &node : nodes) {
      this->SetupMeshes(id);
      id++;
    }
  }

  void Mesh::SetupMeshes(const unsigned int meshId)
  {
    auto meshes = gltfSpec.meshes->GetItems();
    auto mesh = meshes.at(meshId);
    this->SetupPrimitives(mesh.primitives, meshId);
  }

  void Mesh::SetupPrimitives(const Meshes::PrimitiveItems &primitives, const unsigned int meshId)
  {
    auto accessors = gltfSpec.accessors->GetItems();
    for(const auto &primitive : primitives)
    {
      const auto accessorsPrimitive = FindPrimitiveAccessors(primitive);
      const auto verticesSize = PrimitiveVerticesSize(accessorsPrimitive);
      const auto indicesSize = PrimitiveIndicesSize(primitive);
      const auto verticesPosition = primitive.attr.position;
      const auto verticesOffset = PrimitiveIndicesOrVerticesOffset(verticesPosition);
      const auto indicesPosition = *primitive.indices;
      const auto indicesOffset = PrimitiveIndicesOrVerticesOffset(indicesPosition);

      GLBuffer buf{};
      glGenVertexArrays(1, &buf.vao);
      glGenBuffers(1, &buf.vbo);
      glGenBuffers(1, &buf.ebo);
      glBindVertexArray(buf.vao);
      glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
      glBufferData(GL_ARRAY_BUFFER, verticesSize, BufferOffset(verticesOffset), GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, BufferOffset(indicesOffset), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      buf.indicesCount = accessors.at(indicesPosition).count;
      buf.nodeId = meshId;

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
    auto camera = mtEngine::Scenes::Get()->GetCamera();
    auto window = Window::Get();
    auto shader = ResourcesManager::Get()->find<Shader>("default");
    shader->setMat4("projection", camera->GetProjectionMatrix());
    shader->setMat4("view", camera->GetViewMatrix());

    auto nodes = gltfSpec.nodes->GetItems();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for(const auto &buf : _glBuffers)
    {
      auto nodeTranslate = nodes.at(buf.nodeId).translation;
      auto nodeRotation = nodes.at(buf.nodeId).rotation;

      mtEngine::mtVec4f rot = {(float)nodeRotation->x, (float)nodeRotation->y, (float)nodeRotation->z, (float)nodeRotation->w};
      mtEngine::quatToAxisAngle q;
      q = rot;

      glBindVertexArray(buf.vao);
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(nodeTranslate->x, nodeTranslate->y, nodeTranslate->z));
      model = glm::rotate(model, q.angle, glm::vec3(q.x, q.y, q.z));
      shader->setMat4("model", model);
      glDrawElements(GL_TRIANGLES, buf.indicesCount, GL_UNSIGNED_SHORT, nullptr);
      glBindVertexArray(0);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    auto finInd = *gltfSpec.extras->GetSection().gameModelsRelativePath;
    auto binPath = p + finInd + "/" + binFilePath;
    auto binFile = new File(binPath);
    _fileBuffer = binFile->GetBuffer();
    delete binFile;
  }

  const char *Mesh::BufferOffset(const unsigned int &pos)
  {
    auto buffer = _fileBuffer.begin() + pos;

    return buffer.base();
  }

  std::vector<Accessors::Item> Mesh::FindPrimitiveAccessors(const Meshes::PrimitiveItem &item) const
  {
    auto accessors = gltfSpec.accessors->GetItems();

    auto pos = accessors.begin() + item.attr.position;

    std::vector<Accessors::Item> result;

    result.push_back(*pos);

    return result;
  }

  unsigned int Mesh::PrimitiveVerticesSize(const std::vector<Accessors::Item>& accessors) const
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

  unsigned int Mesh::PrimitiveIndicesSize(const Meshes::PrimitiveItem &item) const
  {
    const auto buffers = gltfSpec.bufferViews->GetItems();
    unsigned int bytes = buffers.at(*item.indices).byteLength;

    return bytes;
  }

  unsigned int Mesh::PrimitiveIndicesOrVerticesOffset(const unsigned int position) const
  {
    const auto buffers = gltfSpec.bufferViews->GetItems();
    unsigned int bytes = *buffers.at(position).byteOffset;

    return bytes;
  }
} // namespace mtEngine
