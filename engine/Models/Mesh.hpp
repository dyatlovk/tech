#pragma once

#include <memory>
#include <vector>

#include "Resources/Resource.hpp"


namespace mtEngine
{
    class Mesh : public Resource
    {
    public:
        Mesh() = default;

        ~Mesh() override;

        static std::shared_ptr<Mesh> Create(const std::string &name);

        [[nodiscard]] std::type_index GetTypeIndex() const override
        {
          return typeid(Mesh);
        }

        void CreateBuffers();

        void BindBuffers();

        void SetVertices(std::vector<float> vertices) { this->vertices = vertices; };

        void SetVAO(unsigned int vao) { this->vao = vao; };

        void SetVBO(unsigned int vbo) { this->vbo = vbo; };

        void Clean();

        void Draw();

    private:
        unsigned int vbo;
        unsigned int vao;
        unsigned int ebo;

        std::vector<float> vertices{ 
            0.5f,  0.5f, 0.0f,  // верхняя правая
            0.5f, -0.5f, 0.0f,  // нижняя правая
            -0.5f, -0.5f, 0.0f,  // нижняя левая
            -0.5f,  0.5f, 0.0f
        };
        std::vector<unsigned int> indices {
            0, 1, 3,  // первый треугольник
            1, 2, 3   // второй треугольник
        };
  };
}
