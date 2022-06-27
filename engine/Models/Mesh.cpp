#include "Mesh.hpp"
#include "Resources/ResourcesManager.hpp"
#include <GL/glew.h>

namespace mtEngine {

    Mesh::~Mesh()
    {
        Clean();
    }

    std::shared_ptr<Mesh> Mesh::Create(const std::string &name)
    {
        auto mgr = ResourcesManager::Get();
        if (auto resource = mgr->find<Mesh>(name)) return resource;

        auto resource = std::make_shared<Mesh>();
        resource->CreateBuffers();
        resource->BindBuffers();
        mgr->add(name, resource);

        return resource;
    }

    void Mesh::Clean()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    void Mesh::CreateBuffers()
    {
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
    }

    void Mesh::BindBuffers()
    {
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Mesh::Draw()
    {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
