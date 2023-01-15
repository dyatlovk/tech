#pragma once

#include <filesystem>
#include <memory>

#include "Files/File.hpp"
#include "Models/Mesh.hpp"

namespace mtEngine
{
  class Model : public Component::Registrar<Model>, public Resource
  {
    constexpr static const char *prefix = "model";
    inline static const bool Registered = Register(prefix);

  public:
    explicit Model(std::shared_ptr<Model> model = nullptr);
    ~Model() override;

    static auto Create(const std::filesystem::path &path) -> std::shared_ptr<Model>;

    auto CreateFromFile(const std::filesystem::path &path) -> void;

    void Start() override;

    void Update() override;

    [[nodiscard]] auto GetTypeIndex() const -> std::type_index override { return typeid(Model); }

    std::string GetTypeName() const override { return prefix; };

    void BindNodes();

    void RenderMeshes();

    auto GetName() -> std::string const { return m_name; };

  private:
    const Files::FileGltf::Spec LoadSpecification(const std::filesystem::path &path);
    const std::string LoadGeometry(const std::filesystem::path &path);
    std::shared_ptr<Model> m_model;
    std::vector<std::shared_ptr<Mesh>> m_meshes;

  private:
    std::filesystem::path m_file_path;
    std::string m_fileBuffer;
    Files::FileGltf::Spec m_gltfSpec{};
    std::string m_name;

    void UpdateTransformFromSpec(const Files::Nodes::Item &item);
  };
} // namespace mtEngine
