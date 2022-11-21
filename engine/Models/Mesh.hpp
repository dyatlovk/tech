#pragma once

#include <GL/glew.h>
#include <filesystem>

#include <Devices/Window.hpp>
#include <Files/FileGltf.hpp>
#include <Models/Material.hpp>
#include <Resources/ResourcesManager.hpp>
#include <Scenes/Entity.hpp>
#include <Scenes/Scenes.hpp>

#include "Scenes/Components/Transform.hpp"

namespace mtEngine
{
  class Mesh : public Resource
  {
    constexpr static const char *postfix = "_mesh";

  public:
    Mesh();

    ~Mesh() override;

    static std::shared_ptr<Mesh> Create(
        const uint16_t meshId, const std::string &buffer, const Files::FileGltf::Spec &spec);

    [[nodiscard]] std::type_index GetTypeIndex() const override { return typeid(Mesh); }

    void Update();

  public:
    Transform *_model_transform;
    void SetModelTransform(const Transform *transform) { _model_transform = const_cast<Transform *>(transform); };

  private:
    std::string m_fileBuffer;
    Files::FileGltf::Spec m_gltfSpec;
    Files::Meshes::Item m_meshItem;
    uint16_t m_meshId;

  private:
    struct GLBuffer
    {
      unsigned int vao;
      unsigned int vbo;
      unsigned int ebo;
      unsigned int indicesCount;
    };

    using GLBuffers = std::vector<GLBuffer>;
    GLBuffers m_gl_buffers;

  private:
    std::shared_ptr<Material> m_material;

  private:
    void SetupPrimitives();
    void CleanBuffers();
    [[nodiscard]] std::vector<Files::Accessors::Item> FindPrimitiveAccessors(
        const Files::Meshes::PrimitiveItem &item) const;
    [[nodiscard]] unsigned int PrimitiveVerticesSize(const std::vector<Files::Accessors::Item> &accessors) const;
    [[nodiscard]] unsigned int PrimitiveIndicesSize(const Files::Meshes::PrimitiveItem &item) const;
    [[nodiscard]] unsigned int PrimitiveBufferOffset(const unsigned int position) const;
    [[nodiscard]] unsigned int PrimitiveNormalSize(unsigned int position) const;
    [[nodiscard]] const char *FileBufferOffset(const unsigned int &pos);
    [[nodiscard]] const char *BufferOffset(unsigned int offset);
  };
} // namespace mtEngine
