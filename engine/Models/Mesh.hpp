#pragma once

#include <filesystem>

#include <Devices/Window.hpp>
#include <Files/FileGltf.hpp>
#include <Resources/Resource.hpp>
#include <Resources/ResourcesManager.hpp>

namespace mtEngine
{
  using namespace Files;

  class Mesh : public Resource
  {
    struct GLBuffer;
  public:
    Mesh() = default;

    ~Mesh() override;

    static std::shared_ptr<Mesh> Create(const std::string &name, const std::filesystem::path &path);

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Mesh);
    }

    void CleanBuffers();

    void SetupPrimitives(const Meshes::PrimitiveItems &primitives);

    void SetupMeshes();

    void Draw();

  private:
    void LoadSpecification(const std::filesystem::path &path);
    void LoadGeometry();
    const char *BufferOffset(const unsigned int &pos);

    [[nodiscard]] std::vector<Accessors::Item> FindPrimitiveAccessors(const Meshes::PrimitiveItem &item) const;

    [[nodiscard]] unsigned int PrimitiveVerticesSize(const std::vector<Accessors::Item>& accessors) const;
    [[nodiscard]] unsigned int PrimitiveIndicesSize(const Meshes::PrimitiveItem &item) const;
    [[nodiscard]] unsigned int PrimitiveIndicesOrVerticesOffset(unsigned int position) const;

  private:
    std::string _fileBuffer;

    struct GLBuffer
    {
      unsigned int vao;
      unsigned int vbo;
      unsigned int ebo;
      unsigned int indicesCount;
    };

    std::vector<GLBuffer> _glBuffers;

    FileGltf::Spec gltfSpec{};
  };
} // namespace mtEngine
