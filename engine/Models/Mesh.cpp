#include "Mesh.hpp"

#include "Light/Light.hpp"

namespace mtEngine
{
#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

  Mesh::Mesh()
      : _model_transform(nullptr)
  {
  }

  Mesh::~Mesh()
  {
    CleanResources();
    CleanBuffers();
  }

  std::shared_ptr<Mesh> Mesh::Create(
      const uint16_t meshId, const std::string &buffer, const Files::FileGltf::Spec &spec)
  {
    auto mgr = ResourcesManager::Get();
    const auto meshItem = spec.meshes->FindBy(meshId);
    const auto name = *meshItem.name + POSTFIX;
    PLOGD << "try creating mesh " << name;

    if (auto res = mgr->find<Mesh>(name))
      return res;

    const auto res = std::make_shared<Mesh>();
    res->m_fileBuffer = buffer;
    res->m_gltfSpec = spec;
    res->m_meshItem = meshItem;
    res->m_meshId = meshId;
    res->m_name = name;
    res->SetupPrimitives();

    mgr->add(name, std::dynamic_pointer_cast<Resource>(res));
    return res;
  }

  void Mesh::Update()
  {
    auto nodes = m_gltfSpec.nodes->GetItems();
    auto mat = ResourcesManager::Get()->find<Material>(Material::DEFAULT_NAME);
    auto shader = ResourcesManager::Get()->find<Shader>("default");
    shader->Use();
    auto camera = mtEngine::Scenes::Get()->GetCamera();
    auto window = Window::Get();
    shader->setMat4("projection", camera->GetProjectionMatrix());
    shader->setMat4("view", camera->GetViewMatrix());

    const auto sun = Scenes::Get()->GetStructure()->GetEntity("Sun");
    if (sun)
    {
      const auto sunComponent = sun->GetComponent<Light>();
      shader->setVec3("light.direction", sunComponent->GetDirection());
      shader->setFloat("light.strength", sunComponent->GetStrength());
      shader->setVec3("light.color", sunComponent->GetColor());
    }

    const auto modelTranslate = _model_transform->GetTranslation();
    int _count = 0;
    for (const auto &buf : m_primitives)
    {
      auto nodeTranslate = nodes.at(m_meshId).translation;
      auto nodeRotation = nodes.at(m_meshId).rotation;
      auto nodeScale = nodes.at(m_meshId).scale;

      const auto matItem = FindMaterialItem(_count);
      if (matItem)
      {
        mat = ResourcesManager::Get()->find<Material>(*matItem->name);
      }
      if (!mat)
      {
        shader->setBool("nomaterial", true);
      }

      if (mat)
      {
        shader = mat->GetShader();
        shader->setBool("nomaterial", false);
        mat->Draw();
      }
      if (mat && mat->isDoubleSided())
      {
        glEnable(GL_CULL_FACE);
      }

      glm::mat4 model = glm::mat4(1.0f);
      const auto translate = glm::vec3(nodeTranslate->x, nodeTranslate->y, nodeTranslate->z);
      const auto tr = modelTranslate + translate;
      model = glm::translate(model, tr);
      const auto scale = glm::vec3(nodeScale->x, nodeScale->y, nodeScale->z);
      model = glm::scale(model, scale);
      mtEngine::mtVec4f rot = { (float)nodeRotation->x, (float)nodeRotation->y, (float)nodeRotation->z, (float)nodeRotation->w};
      mtEngine::quatToAxisAngle q;
      q = rot;
      mtEngine::mtVec4f entityRotation = { _model_transform->GetScale().x, _model_transform->GetScale().y, _model_transform->GetScale().z};
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
      _count++;
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
      Primitive _primitive{};
      glGenVertexArrays(1, &_primitive.vao);
      glGenBuffers(1, &_primitive.vbo);
      glGenBuffers(1, &_primitive.ebo);
      glBindVertexArray(_primitive.vao);

      const auto accessorsPrimitive = FindPrimitiveAccessors(primitive);
      const auto verticesBytesLength = PrimitiveVerticesSize(primitive);
      _primitive.verticesSize = verticesBytesLength;
      const auto verticesPosition = primitive.attr.position;
      const auto verticesOffset = PrimitiveBufferOffset(verticesPosition);

      glBindBuffer(GL_ARRAY_BUFFER, _primitive.vbo);
      glBufferData(GL_ARRAY_BUFFER, m_fileBuffer.length(), m_fileBuffer.data(), GL_STATIC_DRAW);

      // positions
      const auto indicesPosition = *primitive.indices;
      const auto indicesSize = PrimitiveIndicesSize(primitive);
      const auto indicesOffset = PrimitiveBufferOffset(indicesPosition);
      const auto posAccessorCount = accessors.at(verticesPosition).count;
      _primitive.posPointer = BUFFER_OFFSET(verticesOffset);
      _primitive.indicesPointer = FileBufferOffset(indicesOffset);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * 3, _primitive.posPointer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _primitive.ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, FileBufferOffset(indicesOffset), GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);

      // normals
      const auto normalPosition = primitive.attr.normal;
      const auto normalSize = PrimitiveNormalSize(normalPosition);
      const auto normalOffset = PrimitiveBufferOffset(normalPosition);
      const auto normalAccessorCount = accessors.at(normalPosition).count;
      _primitive.normPointer = BUFFER_OFFSET(normalOffset);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * 3, _primitive.normPointer);
      glEnableVertexAttribArray(1);

      // textures
      const auto texPosition = primitive.attr.textcoord_0;
      const auto texOffset = PrimitiveBufferOffset(primitive.attr.textcoord_0);
      const auto texSize = PrimitiveNormalSize(texPosition);
      _primitive.texPointer = BUFFER_OFFSET(texOffset);
      const auto texAccessorCount = accessors.at(texPosition).count;
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * 2, _primitive.texPointer);
      glEnableVertexAttribArray(2);

      _primitive.indicesCount = accessors.at(indicesPosition).count;

      m_primitives.push_back(_primitive);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

      if (primitive.material)
      {
        Material::Create(*primitive.material, m_gltfSpec);
      }
      else
      {
        Material::CreateDefault();
      }
    }
  }

  void Mesh::CleanBuffers()
  {
    for (const auto &buf : m_primitives)
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

  unsigned int Mesh::PrimitiveVerticesSize(const Files::Meshes::PrimitiveItem &primitive) const
  {
    unsigned int bytes = 0;
    const auto buffers = m_gltfSpec.bufferViews->GetItems();
    const auto endAt = primitive.indices;
    bytes = *buffers.at(*endAt).byteOffset + buffers.at(*endAt).byteLength;

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

  auto Mesh::FindMaterialItem() -> Files::Materials::Item *const
  {
    const auto matId = m_meshItem.primitives.at(0).material;
    if (!matId)
      return nullptr;
    const auto matItem = m_gltfSpec.materials->GetItems().at(*matId);

    return new Files::Materials::Item(matItem);
  }

  auto Mesh::FindMaterialItem(const int primitiveId) -> Files::Materials::Item *const
  {
    const auto matId = m_meshItem.primitives.at(primitiveId).material;
    if (!matId)
      return nullptr;
    const auto matItem = m_gltfSpec.materials->GetItems().at(*matId);

    return new Files::Materials::Item(matItem);
  }

  auto Mesh::FindTextureItem() -> Files::Textures::Item *const
  {
    const auto imgs = m_gltfSpec.images->GetItems();

    return nullptr;
  }

  auto Mesh::CleanResources() -> void
  {
    const auto matItemFound = FindMaterialItem();
    if (matItemFound)
      ResourcesManager::Get()->remove(*matItemFound->name);

    const auto imgs = m_gltfSpec.images->GetItems();
    for (const auto &i : *imgs)
    {
      ResourcesManager::Get()->remove(*i.name);
    }

    m_primitives.clear();
    m_fileBuffer.clear();
    m_gltfSpec = {};
    m_meshItem = {};
    PLOGD << "mesh res clean: " << m_name;
  }
} // namespace mtEngine
