#pragma once

#include <memory>

#include <Scenes/Scenes.hpp>

#include "Config.hpp"
#include "Graphics/Shader.hpp"

namespace Game
{
  using namespace mtEngine;

  class Grid
  {
  public:
    Grid()
    {
      const std::string p(RESOURCES);
      Shader::Create("grid", p + "/Game/shaders/grid.vs", p + "/Game/shaders/grid.fs", nullptr);

      glGenVertexArrays(1, &VAO);
      glGenBuffers(1, &VBO);
      glGenBuffers(1, &EBO);

      glBindVertexArray(VAO);
      glBindBuffer(GL_ARRAY_BUFFER, VBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)nullptr);

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    };

    ~Grid()
    {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
      glDeleteBuffers(1, &EBO);
    };

    void Update()
    {
      auto shader = ResourcesManager::Get()->find<Shader>("grid");
      auto camera = mtEngine::Scenes::Get()->GetCamera();
      if (shader)
      {
        shader->Use();
        shader->setMat4("projection", camera->GetProjectionMatrix());
        shader->setMat4("view", camera->GetViewMatrix());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader->setMat4("model", model);
      }
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
      glBindVertexArray(0);
    };

  private:
    unsigned int VBO, VAO, EBO;

    float vertices[12]{1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f};

    unsigned int indices[6] = {0, 1, 3, 1, 2, 3};
  };
}; // namespace Game
