#pragma once

#include <memory>
#include <filesystem>

#include "Files/File.hpp"
#include <Files/FileGltf.hpp>

namespace mtEngine::SceneManager
{
  using namespace Files;

  class SceneManager;
  class Node;
  class Mesh;
  class Primitive;
  class Material;
  class Shader;

  //////////////////////////////////////////////////////////////////////////////
  // SceneManager
  //////////////////////////////////////////////////////////////////////////////
  class SceneManager
  {
  public:
    struct SceneItem;

    SceneManager();
    ~SceneManager();

    // @brief Load and parse *.gltf file
    const FileGltf::Spec &LoadSpecification(const std::filesystem::path &path);

    // @brief Load binary geometry from buffer.uri path
    const std::string &LoadGeometry(const std::string &binFileName);

    // @brief Create scene from gltf file
    static std::shared_ptr<SceneManager> CreateFromGltf(const std::filesystem::path &path);

    // @broef Get created scene structure
    const SceneItem &GetScene() { return static_cast<SceneItem &>(scene); };

    void SetupScene();
    void ParseNodes();
    const FileGltf::Spec *GetSpec() { return &gltfSpec; };

  public:
    struct SceneItem
    {
      std::vector<Node> nodes;
      std::string name;
    } scene;

  private:
    std::string _geometryBuffer;
    std::string _fileTmpBuf;
    FileGltf::Spec gltfSpec;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Node
  //////////////////////////////////////////////////////////////////////////////
  class Node
  {
  public:
    struct Item;
    Node(const Files::Nodes::Item &item, const Files::Meshes::Item &_meshItem);
    ~Node();

  public:
    struct Item
    {
      std::vector<Mesh> meshes;
      std::string name;
    } node;

    void Setup();

  private:
    nlohmann::json::array_t *json;
    Files::Nodes::Item _item;
    Files::Meshes::Item _meshItem;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Mesh
  //////////////////////////////////////////////////////////////////////////////
  class Mesh
  {
  public:
    struct Item;
    Mesh(const Files::Meshes::Item &item);
    ~Mesh();

  public:
    struct Item
    {
      std::vector<Primitive> primitives;
    };

  private:
    Files::Meshes::Item _item;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Primitives
  //////////////////////////////////////////////////////////////////////////////
  class Primitive
  {
  public:
    struct Item;
    Primitive();
    ~Primitive();

  public:
    struct Item
    {
      Material *material;
      Shader *shader = nullptr;
    };
  };

  //////////////////////////////////////////////////////////////////////////////
  // Material
  //////////////////////////////////////////////////////////////////////////////
  class Material
  {
  public:
    Material();
    ~Material();
  };

  //////////////////////////////////////////////////////////////////////////////
  // Shader
  //////////////////////////////////////////////////////////////////////////////
  class Shader
  {
  public:
    Shader();
    ~Shader();
  };
} // namespace mtEnginem::Scenes
