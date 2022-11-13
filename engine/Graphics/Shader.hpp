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

    static std::shared_ptr<Shader> Create(const std::string &name, const std::string &vert, const std::string &frag, const std::string *geom = nullptr);

    static std::shared_ptr<Shader> CreateDefault();


    void VertCompile(const std::string *buffer = nullptr);

    void FragCompile(const std::string *buffer = nullptr);

    void GeomCompile(const std::string *buffer = nullptr);

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

    void setVec2(const std::string &name, const glm::vec2 &value)
    {
      glUniform2fv(glGetUniformLocation(pid, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, const glm::vec3 &value)
    {
      glUniform3f(glGetUniformLocation(pid, name.c_str()), value.x, value.y, value.z);
    }

  private:
    int pid;

    int vert;
    int frag;
    int geom;

  private:
    const char *vertexShaderDefaultSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "}\0";
        
    const char *fragmentShaderDefaultSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   float ambientStrength = 0.8;\n"
        "   vec3 objectColor = vec4(0.43f, 0.6f, 0.52f);\n"
        "   vec3 lightColor = vec4(1.00f, 1.00f, 1.00f);\n"
        "   vec3 ambient = ambientStrength * lightColor;\n"
        "   vec3 result = ambient * objectColor;\n"
        "   FragColor = vec4(result, 1.0);\n"
        "}\0";

    const char *geometrySource =
        "#version 330 core\n"
        "layout (points) in;\n"
        "layout (points, max_vertices = 1) out;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = gl_in[0].gl_Position;\n"
        "   EmitVertex();\n"
        "   EndPrimitive();\n"
        "}\0";
  };
} // namespace mtEngine
