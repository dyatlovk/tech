#pragma once

#include "Resources/Resource.hpp"
#include "Resources/ResourcesManager.hpp"

#include <GL/glew.h>
#include <third_party/glm/glm.hpp>

namespace mtEngine
{
  class Shader : public Resource
  {
  public:
    Shader() = default;

    static std::shared_ptr<Shader> Create(const std::string &name);

    static std::shared_ptr<Shader> CreateDefault();

    void VertCompile();

    void FragCompile();

    void Link();

    void Use();

    int GetPid() { return pid; };

    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
      return typeid(Shader);
    }

    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
      glUniformMatrix4fv(glGetUniformLocation(pid, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

  private:
    int pid;

    int vert;
    int frag;
    int geom;

  private:
    bool isMainThread();

  private:
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.43f, 0.6f, 0.52f, 0.4f);\n"
        "}\n\0";
  };
} // namespace mtEngine
