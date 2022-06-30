#include <GL/glew.h>
#include "Shader.hpp"

namespace mtEngine
{
  std::shared_ptr<Shader> Shader::Create(const std::string &name)
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Shader>(name))
      return resource;

    auto resource = std::make_shared<Shader>();
    resource->VertCompile();
    resource->FragCompile();
    resource->Link();
    mgr->add(name, resource);

    return resource;
  }

  std::shared_ptr<Shader> Shader::CreateDefault()
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Shader>("default"))
      return resource;

    auto resource = std::make_shared<Shader>();
    resource->VertCompile();
    resource->FragCompile();
    resource->Link();
    mgr->add("default", resource);

    return resource;
  }

  void Shader::Use() { 
    glUseProgram(pid);
  }

  void Shader::VertCompile()
  {
    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertexShaderSource, nullptr);
    glCompileShader(vert);

    int success;
    char infoLog[512];
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(vert, 512, nullptr, infoLog);
      PLOGD << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog;
    }
    PLOGI << "Shader vert compiled";
  }

  void Shader::FragCompile()
  {
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragmentShaderSource, NULL);
    glCompileShader(frag);

    int success;
    char infoLog[512];
    // Проверка на наличие ошибок компилирования шейдера
    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(frag, 512, nullptr, infoLog);
      PLOGD << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog;
    }

    PLOGI << "Shader frag compiled";
  }

  void Shader::Link()
  {
    pid = glCreateProgram();
    glAttachShader(pid, vert);
    glAttachShader(pid, frag);
    glLinkProgram(pid);

    int success;
    char infoLog[512];
    // Проверка на наличие ошибок связывания шейдеров
    glGetProgramiv(pid, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(pid, 512, NULL, infoLog);
      PLOGD << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << infoLog;
    }
    glDeleteShader(vert);
    glDeleteShader(frag);

    PLOGI << "Shaders linked";
  }
} // namespace mtEngine
