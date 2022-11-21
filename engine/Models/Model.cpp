#include "Model.hpp"
#include <Scenes/Components/Transform.hpp>

namespace mtEngine
{
  Model::Model(std::shared_ptr<Model> model)
      : m_model(std::move(model))
  {
    if (m_model)
    {
      m_file_path = m_model.get()->m_file_path;
      m_gltfSpec = m_model.get()->m_gltfSpec;
      m_fileBuffer = m_model.get()->m_fileBuffer;
      BindNodes();
    }
  }

  auto Model::Create(const std::filesystem::path &path) -> std::shared_ptr<Model>
  {
    PLOGD << "try creating model " << path;
    const std::size_t hash = std::hash<std::string>{}(path);
    const std::string name = std::to_string(hash);

    auto mgr = ResourcesManager::Get();
    if (auto res = mgr->find<Model>(name))
      return res;

    auto res = std::make_shared<Model>();
    res->CreateFromFile(path);
    mgr->add(name, std::dynamic_pointer_cast<Resource>(res));

    return res;
  }

  void Model::Start() {}

  auto Model::CreateFromFile(const std::filesystem::path &path) -> void
  {
    m_gltfSpec = LoadSpecification(path);

    const std::string p(RESOURCES);
    const auto binFile = *m_gltfSpec.buffers->GetItems().at(0).uri;
    const auto binFindPath = m_gltfSpec.scenes->GetSection().extras->BinPath;
    const auto binPath = p + binFindPath + "/" + binFile;
    m_fileBuffer = LoadGeometry(binPath);
  }

  void Model::BindNodes()
  {
    auto nodes = m_gltfSpec.nodes->GetItems();
    for (const auto &node : nodes)
    {
      const auto meshPos = node.mesh;
      if (meshPos)
      {
        const auto mesh = Mesh::Create(*meshPos, m_fileBuffer, m_gltfSpec);
        m_meshes.push_back(mesh);
      }
    }
  }

  void Model::Update()
  {
    auto transform = GetEntity()->GetComponent<Transform>();
    for (const auto &mesh : m_meshes)
    {
      mesh->SetModelTransform(transform);
      mesh->Update();
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  const std::string Model::LoadGeometry(const std::filesystem::path &path)
  {
    if (!m_gltfSpec.buffers)
    {
      PLOGE << "gltf specification not loaded";
      return "";
    }

    auto binFile = new File(path);
    const auto buffer = std::string(binFile->GetBuffer());
    delete binFile;

    return buffer;
  }

  const Files::FileGltf::Spec Model::LoadSpecification(const std::filesystem::path &path)
  {
    auto gltf = Files::FileGltf::Create(path);

    return gltf->GetSpecification();
  }
} // namespace mtEngine
