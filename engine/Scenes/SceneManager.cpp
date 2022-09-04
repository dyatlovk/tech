#include "SceneManager.hpp"
#include <stdexcept>
#include "Config.hpp"

////////////////////////////////////////////////////////////////////////////////
// SceneManager
////////////////////////////////////////////////////////////////////////////////
namespace mtEngine::SceneManager
{
  SceneManager::SceneManager()
  {

  }

  SceneManager::~SceneManager()
  {
    _geometryBuffer.clear();
    _fileTmpBuf.clear();
  }

  std::shared_ptr<SceneManager> SceneManager::CreateFromGltf(const std::filesystem::path &path)
  {
    auto scene = std::make_shared<SceneManager>();
    scene->gltfSpec = scene->LoadSpecification(path);

    const std::string binUri = *scene->gltfSpec.buffers->GetItems().at(0).uri;
    scene->_geometryBuffer = scene->LoadGeometry(binUri);
    scene->_fileTmpBuf.clear();
    scene->SetupScene();

    return scene;
  }

  void SceneManager::SetupScene()
  {
    auto s = gltfSpec.scenes->GetSection();
    auto nodeJson = gltfSpec.nodes->GetItems();
    scene.name = *s.name;

    for (const auto &n : s.nodes)
    {
      auto nodeJsonItem = nodeJson.at(n);
      auto meshId = *nodeJsonItem.mesh;
      auto mesh = gltfSpec.meshes->FindBy(meshId);
      auto node = new Node(nodeJsonItem, mesh);
      scene.nodes.push_back(*node);
      delete node;
    }
  }

  const FileGltf::Spec &SceneManager::LoadSpecification(const std::filesystem::path &path)
  {
    auto gltf = FileGltf::Create(path);

    return gltf->GetSpecification();
  }

  const std::string &SceneManager::LoadGeometry(const std::string &binFileName)
  {
    const std::string p(RESOURCES);
    if (!gltfSpec.buffers)
    {
      PLOGF << "gltf specification not loaded";
      _fileTmpBuf = "";
      return _fileTmpBuf;
    }

    if(!gltfSpec.extras->GetSection().gameScenesRelativePath)
    {
      PLOGF << "gltf specification not loaded";
      _fileTmpBuf = "";
      return _fileTmpBuf;
    }

    auto binPath = p + *gltfSpec.extras->GetSection().gameScenesRelativePath + "/" + binFileName;
    auto buffer = new File(binPath);
    _fileTmpBuf = buffer->GetBuffer();
    delete buffer;

    return _fileTmpBuf;
  }
}


////////////////////////////////////////////////////////////////////////////////
// Node
////////////////////////////////////////////////////////////////////////////////
namespace mtEngine::SceneManager
{
  Node::Node(const Files::Nodes::Item &item, const Files::Meshes::Item &_meshItem): _item(item), _meshItem(_meshItem)
  {
    Setup();
  }

  Node::~Node() = default;

  void Node::Setup()
  {
    if (!_item.mesh)
    {
      throw std::runtime_error("mesh not found in node");
    }
    node.name = *_item.name;
    auto mesh = new Mesh(_meshItem);
    node.meshes.push_back(*mesh);
    delete mesh;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Mesh
////////////////////////////////////////////////////////////////////////////////
namespace mtEngine::SceneManager {
  Mesh::Mesh(const Files::Meshes::Item &item): _item(item)
  {

  }

  Mesh::~Mesh()
  {

  }
}
