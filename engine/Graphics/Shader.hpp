#pragma once

#include <memory>
#include "Resources/ResourcesManager.hpp"
#include "Resources/Resource.hpp"
#include <iostream>
#include "Devices/Window.hpp"

namespace mtEngine {
    class Shader : public Resource
    {
    public:
        Shader() = default;

        static std::shared_ptr<Shader> Create(const std::string &name);

        void VertCompile();

        void FragCompile();

        void Link();

        void Use();

        int GetPid() { return pid; };

        [[nodiscard]] std::type_index GetTypeIndex() const override
        {
          return typeid(Shader);
        }
    private:
        int pid;

        int vert;
        int frag;
        int geom;

    private:
        const char* vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char* fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";
    };
}
