#include "../include/app.hpp"
#include "Devices/Window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Editor {
  using namespace mtEngine;
  EditorApp::EditorApp(): App("Test") {

  }

  EditorApp::~EditorApp() {

  }

  void EditorApp::Start() {
  }

  void EditorApp::Update()
  {
    auto window = mtEngine::Window::Get()->GetWindow();
     glClear(GL_COLOR_BUFFER_BIT);
     glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
     glfwSwapBuffers(window);
  }
}
