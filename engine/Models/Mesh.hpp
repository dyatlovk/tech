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
    void SetModelTransform(const Transform *transform) { _model_transform = const_cast<Transform *>(transform); }

  private:
    std::string m_fileBuffer;
    Files::FileGltf::Spec m_gltfSpec;
    Files::Meshes::Item m_meshItem;
    uint16_t m_meshId;

  private:
    struct Primitive
    {
      unsigned int vao;
      unsigned int vbo;
      unsigned int ebo;
      unsigned int indicesCount;
      unsigned int verticesSize;
      const char *posPointer = nullptr;
      const char *normPointer = nullptr;
      const char *texPointer = nullptr;
      const char *indicesPointer = nullptr;
    };

    using Primitives = std::vector<Primitive>;
    Primitives m_primitives;

  private:
    std::shared_ptr<Material> m_material;

  private:
    void SetupPrimitives();
    void CleanBuffers();
    [[nodiscard]] std::vector<Files::Accessors::Item> FindPrimitiveAccessors(
        const Files::Meshes::PrimitiveItem &item) const;
    [[nodiscard]] unsigned int PrimitiveVerticesSize(const Files::Meshes::PrimitiveItem &primitive) const;
    [[nodiscard]] unsigned int PrimitiveIndicesSize(const Files::Meshes::PrimitiveItem &item) const;
    [[nodiscard]] unsigned int PrimitiveBufferOffset(const unsigned int position) const;
    [[nodiscard]] unsigned int PrimitiveNormalSize(unsigned int position) const;
    [[nodiscard]] const char *FileBufferOffset(const unsigned int &pos);
    [[nodiscard]] const char *BufferOffset(unsigned int offset);

  private:
    static inline int32_t GetComponentSizeInBytes(uint32_t componentType) {
      if (componentType == 5120) {
        return 1;
      } else if (componentType == 5121) {
        return 1;
      } else if (componentType == 5122) {
        return 2;
      } else if (componentType == 5123) {
        return 2;
      } else if (componentType == 5124) {
        return 4;
      } else if (componentType == 5125) {
        return 4;
      } else if (componentType == 5126) {
        return 4;
      } else if (componentType == 5130) {
        return 8;
      } else {
        // Unknown component type
        return -1;
      }
    }
  };
} // namespace mtEngine
