#include "Mesh.hpp"

#include <Maths/Vectors/Vector4d.hpp>

#include "Maths/Transformation.hpp"
#include "Models/Material.hpp"
#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

  Mesh::Mesh()
      : _model_transform(nullptr)
      , m_material(nullptr)
  {
  }

  Mesh::~Mesh()
  {
    CleanBuffers();
  }

  std::shared_ptr<Mesh> Mesh::Create(
      const uint16_t meshId, const std::string &buffer, const Files::FileGltf::Spec &spec)
  {
    auto mgr = ResourcesManager::Get();
    const auto meshItem = spec.meshes->FindBy(meshId);
    const auto name = *meshItem.name + postfix;
    PLOGD << "try creating mesh " << name;

    if (auto res = mgr->find<Mesh>(name))
      return res;

    const auto res = std::make_shared<Mesh>();
    res->m_fileBuffer = buffer;
    res->m_gltfSpec = spec;
    res->m_meshItem = meshItem;
    res->m_meshId = meshId;
    res->SetupPrimitives();

    mgr->add(name, std::dynamic_pointer_cast<Resource>(res));
    return res;
  }

  void Mesh::Update()
  {
    auto shader = m_material->GetShader();
    shader->Use();
    if (m_material->isDefault())
    {
      shader->setBool("nomaterial", true);
    }
    if (!m_material->isDefault())
    {
      shader->setBool("nomaterial", false);
      m_material->Draw();
    }
    auto camera = mtEngine::Scenes::Get()->GetCamera();
    auto window = Window::Get();
    shader->setMat4("projection", camera->GetProjectionMatrix());
    shader->setMat4("view", camera->GetViewMatrix());
    auto nodes = m_gltfSpec.nodes->GetItems();
    shader->setVec3("light.position", glm::vec3(10.0, 5.0, 1.0));
    if (!m_material->isDoubleSided())
    {
      glEnable(GL_CULL_FACE);
    }
    glFrontFace(GL_CCW);
    for (const auto &buf : m_gl_buffers)
    {
      auto nodeTranslate = nodes.at(m_meshId).translation;
      auto nodeRotation = nodes.at(m_meshId).rotation;
      auto nodeScale = nodes.at(m_meshId).scale;

      glm::mat4 model = glm::mat4(1.0f);
      const auto translate = glm::vec3(nodeTranslate->x, nodeTranslate->y, nodeTranslate->z) + _model_transform->GetTranslation();
      model = glm::translate(model, translate);
      const auto scale = glm::vec3(nodeScale->x, nodeScale->y, nodeScale->z);
      model = glm::scale(model, scale);
      mtEngine::mtVec4f rot = { (float)nodeRotation->x, (float)nodeRotation->y, (float)nodeRotation->z, (float)nodeRotation->w };
      mtEngine::quatToAxisAngle q;
      q = rot;
      mtEngine::mtVec4f entityRotation = {_model_transform->GetScale().x, _model_transform->GetScale().y, _model_transform->GetScale().z};
      mtEngine::quatToAxisAngle entityQuat;
      entityQuat = entityRotation;
      if ((rot.x + rot.y + rot.z) > 0)
      {
        const auto rotation = glm::vec3(q.x, q.y, q.z) + glm::vec3(entityQuat.x, entityQuat.y, entityQuat.z);
        const auto angle = q.angle + entityQuat.angle;
        model = glm::rotate(model, glm::radians(angle), rotation);
      }
      shader->setMat4("model", model);

      glBindVertexArray(buf.vao);
      glDrawElements(GL_TRIANGLES, buf.indicesCount, GL_UNSIGNED_SHORT, nullptr);
      glBindVertexArray(0);
    }
    glDisable(GL_CULL_FACE);
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  void Mesh::SetupPrimitives()
  {
    const auto primitives = m_meshItem.primitives;
    auto accessors = m_gltfSpec.accessors->GetItems();

    for (const auto &primitive : primitives)
    {
      GLBuffer buf{};
      glGenVertexArrays(1, &buf.vao);
      glGenBuffers(1, &buf.vbo);
      glGenBuffers(1, &buf.ebo);
      glBindVertexArray(buf.vao);

      const auto accessorsPrimitive = FindPrimitiveAccessors(primitive);
      const auto verticesBytesLength = PrimitiveVerticesSize(accessorsPrimitive);
      const auto verticesPosition = primitive.attr.position;
      const auto verticesOffset = PrimitiveBufferOffset(verticesPosition);

      glBindBuffer(GL_ARRAY_BUFFER, buf.vbo);
      glBufferData(GL_ARRAY_BUFFER, verticesBytesLength, FileBufferOffset(verticesOffset), GL_STATIC_DRAW);

      // positions
      const auto indicesPosition = *primitive.indices;
      const auto indicesSize = PrimitiveIndicesSize(primitive);
      const auto indicesOffset = PrimitiveBufferOffset(indicesPosition);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(verticesOffset));
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, FileBufferOffset(indicesOffset), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);

      // normals
      const auto normalPosition = primitive.attr.normal;
      const auto normalSize = PrimitiveNormalSize(normalPosition);
      const auto normalOffset = PrimitiveBufferOffset(normalPosition);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(normalOffset));
      glEnableVertexAttribArray(1);

      // textures
      const auto texPosition = primitive.attr.textcoord_0;
      const auto texOffset = PrimitiveBufferOffset(primitive.attr.textcoord_0);
      const auto texSize = PrimitiveNormalSize(texPosition);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(texOffset));
      glEnableVertexAttribArray(2);

      buf.indicesCount = accessors.at(indicesPosition).count;

      glBindVertexArray(0);
      m_gl_buffers.push_back(buf);

      if (primitive.material)
      {
        m_material = Material::Create(*primitive.material, m_gltfSpec);
      }
      else
      {
        m_material = Material::CreateDefault();
      }
    }
  }

  void Mesh::CleanBuffers()
  {
    for (const auto &buf : m_gl_buffers)
    {
      glDeleteVertexArrays(1, &buf.vao);
      glDeleteBuffers(1, &buf.vbo);
      glDeleteBuffers(1, &buf.ebo);
    }
  }

  std::vector<Files::Accessors::Item> Mesh::FindPrimitiveAccessors(const Files::Meshes::PrimitiveItem &item) const
  {
    auto accessors = m_gltfSpec.accessors->GetItems();

    auto pos = accessors.begin() + item.attr.position;

    std::vector<Files::Accessors::Item> result;

    result.push_back(*pos);

    return result;
  }

  unsigned int Mesh::PrimitiveVerticesSize(const std::vector<Files::Accessors::Item> &accessors) const
  {
    unsigned int bytes = 0;
    const auto buffers = m_gltfSpec.buffers->GetItems();
    for (const auto &buf : buffers)
    {
      bytes += buf.byteLength;
    }

    return bytes;
  }

  unsigned int Mesh::PrimitiveIndicesSize(const Files::Meshes::PrimitiveItem &item) const
  {
    const auto buffers = m_gltfSpec.bufferViews->GetItems();
    unsigned int bytes = buffers.at(*item.indices).byteLength;

    return bytes;
  }

  unsigned int Mesh::PrimitiveBufferOffset(const unsigned int position) const
  {
    const auto buffers = m_gltfSpec.bufferViews->GetItems();
    const auto bytes = buffers.at(position).byteOffset;

    return *bytes;
  }

  const char *Mesh::FileBufferOffset(const unsigned int &pos)
  {
    auto buffer = m_fileBuffer.begin();
    auto result = buffer.base() + pos;

    return result;
  }

  unsigned int Mesh::PrimitiveNormalSize(unsigned int position) const
  {
    const auto buffers = m_gltfSpec.bufferViews->GetItems();
    unsigned int bytes = buffers.at(position).byteLength;

    return bytes;
  }
} // namespace mtEngine
