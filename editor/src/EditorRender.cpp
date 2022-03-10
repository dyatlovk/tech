#include "EditorRender.hpp"
#include "Graphics/Graphics.hpp"
#include <iostream>

namespace Editor {
  EditorRender::EditorRender() = default;

  void EditorRender::Start()
  {
    std::cout << "start render" << std::endl;
  }

  void EditorRender::Update()
  {
    auto window = mtEngine::Window::Get()->GetWindow();
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glfwSwapBuffers(window);
  }
}
