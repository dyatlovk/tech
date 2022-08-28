#pragma once

#include <filesystem>
#include <Devices/Window.hpp>
#include <Resources/Resource.hpp>
#include <Resources/ResourcesManager.hpp>
#include <Files/FileGltf.hpp>


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

    void CreateBuffers();

    void BindBuffers();

    void CleanBuffers();

    void SetupPrimitives();

    void Draw();

  private:
    void LoadSpecification(const std::filesystem::path &path);
    void LoadGeometry();
    const char *BufferOffset(const unsigned int &bytes);

    std::vector<Accessors::Item> FindPrimitiveAccessors(const Meshes::PrimitiveItem &item);

    unsigned int PrimitiveVerticesSize(std::vector<Accessors::Item> accessors);
    unsigned int PrimitiveIndecesSize(const Meshes::PrimitiveItem &item);
    unsigned int PrimitiveIndecesOffset(const unsigned int position);

  private:
    std::string _fileBuffer;

    struct GLBuffer
    {
      unsigned int vao;
      unsigned int vbo;
      unsigned int ebo;
      unsigned int indecesCount;
    };

    std::vector<GLBuffer> _glBuffers;

    FileGltf::Spec gltfSpec{};
  };
} // namespace mtEngine
