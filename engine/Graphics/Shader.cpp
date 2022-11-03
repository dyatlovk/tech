#include <GL/glew.h>
#include "Shader.hpp"
#include "Files/File.hpp"

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

  std::shared_ptr<Shader> Shader::Create(const std::string &name, const std::string &vert, const std::string &frag, const std::string &geom)
  {
    auto mgr = ResourcesManager::Get();
    if (auto resource = mgr->find<Shader>(name))
      return resource;

    auto resource = std::make_shared<Shader>();

    auto fileVert = new File();
    fileVert->Load(vert);
    auto vertBuf = fileVert->GetBuffer();
    resource->VertCompile(&vertBuf);
    fileVert = nullptr;


    auto fileFrag = new File();
    fileFrag->Load(vert);
    auto vertFrag = fileFrag->GetBuffer();
    resource->FragCompile(&vertFrag);

    auto geomFile = new File();
    geomFile->Load(geom);
    auto geomBuf = geomFile->GetBuffer();
    resource->GeomCompile(&geomBuf);

    resource->Link();
    mgr->add(name, resource);

    return resource;
  }

  void Shader::Use() {
    glUseProgram(pid);
  }

  void Shader::VertCompile(const std::string *buffer)
  {
    vert = glCreateShader(GL_VERTEX_SHADER);
    if(buffer) {
      const std::string a = vertexShaderDefaultSource;
      buffer = &a;
      vertexShaderDefaultSource = buffer->c_str();
    }
    glShaderSource(vert, 1, &vertexShaderDefaultSource, nullptr);
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

  void Shader::FragCompile(const std::string *buffer)
  {
    frag = glCreateShader(GL_FRAGMENT_SHADER);
    if(buffer) {
      const std::string a = fragmentShaderDefaultSource;
      buffer = &a;
      fragmentShaderDefaultSource = buffer->c_str();
    }
    glShaderSource(frag, 1, &fragmentShaderDefaultSource, NULL);
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

  void Shader::GeomCompile(const std::string *buffer)
  {
    geom = glCreateShader(GL_GEOMETRY_SHADER);
    if(buffer) {
      const std::string a = geometrySource;
      buffer = &a;
      geometrySource = buffer->c_str();
    }

    glShaderSource(geom, 1, &geometrySource, NULL);
    glCompileShader(geom);

    int success;
    char infoLog[512];
    // Проверка на наличие ошибок компилирования шейдера
    glGetShaderiv(geom, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(geom, 512, nullptr, infoLog);
      PLOGD << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED" << infoLog;
    }

    PLOGI << "Shader frag compiled";
  }

  void Shader::Link()
  {
    pid = glCreateProgram();
    glAttachShader(pid, vert);
    glAttachShader(pid, frag);
    glAttachShader(pid, geom);
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
    glDeleteShader(geom);

    PLOGI << "Shaders linked";
  }
} // namespace mtEngine
