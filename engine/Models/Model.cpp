#include "Model.hpp"

#include "Resources/ResourcesManager.hpp"

namespace mtEngine
{
    Model::Model(const Shader *shader, const Mesh *mesh)
    {
        this->mesh = const_cast<Mesh*>(mesh);
        this->shader = const_cast<Shader*>(shader);
    }

    std::shared_ptr<Model> Model::Create(const std::string &name, const Shader *shader, const Mesh *mesh)
    {
        auto mgr = ResourcesManager::Get();
        if (auto resource = mgr->find<Model>(name)) return resource;

        auto resource = std::make_shared<Model>(shader, mesh);
        mgr->add(name, resource);

        return resource;
    }

    void Model::Draw()
    {
        shader->Use();
        mesh->Draw();
    }
}
