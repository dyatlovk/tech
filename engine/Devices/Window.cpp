#include "Window.hpp"
#include "Engine/Engine.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace mtEngine {
  void CallbackFramebufferSize(GLFWwindow *window, int32_t width, int32_t height)
  {
    Window::Get()->size = {width, height};
  }

  void CallbackWindowClose(GLFWwindow *window)
  {
    Engine::Get()->RequestClose();
    Window::Get()->onClose();
  }

  Window::Window()
  {
    if (glfwInit() == GLFW_FALSE)
      throw std::runtime_error("GLFW failed to initialize");

    window = glfwCreateWindow(1024, 768, "Test", nullptr, nullptr);

    if (!window) {
      glfwTerminate();
      throw std::runtime_error("GLFW failed to create the window");
    }

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    glfwSetWindowCloseCallback(window, CallbackWindowClose);
    glfwSetFramebufferSizeCallback(window, CallbackFramebufferSize);
    glfwSetWindowCloseCallback(window, CallbackWindowClose);
  }

  Window::~Window()
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void Window::Update()
  {
    glfwPollEvents();
  }
}
