#include "Material.hpp"
#include <GL/glew.h>

namespace mtEngine
{
  auto Material::Create(const std::string &name, const Texture *texture) -> std::shared_ptr<Material>
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Material>(name))
      return resource;

    auto resource = std::make_shared<Material>();
    resource->m_texture = const_cast<Texture *>(texture);
    mgr->add(name, resource);

    return resource;
  }

  void Material::Draw()
  {
    if(m_texture){
      m_texture->Update();
    }
  }
} // namespace mtEngine
