#include "Window.hpp"
#include "Engine/Engine.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
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

  void CallbackWindowSize(GLFWwindow *window, int32_t width, int32_t height)
  {
    if (width <= 0 || height <= 0) return;
    Window::Get()->onSize(Window::Get()->size);
  }

  Window::Window(): title("Demo")
  {
    PLOGD << "window started";
    if (glfwInit() == GLFW_FALSE)
      throw std::runtime_error("GLFW failed to initialize");

    window = glfwCreateWindow(1024, 768, title.c_str(), nullptr, nullptr);

    if (!window) {
      glfwTerminate();
      throw std::runtime_error("GLFW failed to create the window");
    }

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    glfwSetWindowCloseCallback(window, CallbackWindowClose);
    glfwSetFramebufferSizeCallback(window, CallbackFramebufferSize);
    glfwSetWindowSizeCallback(window, CallbackWindowSize);

    if (glfwRawMouseMotionSupported())
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  Window::~Window()
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }
  
  void Window::BeforeUpdate()
  {
  }

  void Window::Update()
  {
    glfwPollEvents();
  }
  
  void Window::AfterUpdate()
  {
    // glfwSwapBuffers(window);
  }

  void Window::SetFullscreen(bool fullscreen)
  {
    this->fullscreen = fullscreen;
  }

  void Window::SetPosition(const std::array<int, 2> &pos)
  {
    glfwSetWindowPos(window, pos[0], pos[1]);
  }

  void Window::MaximizeToggle()
  {
    if(isMaximized) {
      glfwRestoreWindow(window);
    } else {
      glfwMaximizeWindow(window);
    }
    isMaximized =! isMaximized;
  }

  void Window::Maximize(bool state)
  {
    if(state) {
      glfwMaximizeWindow(window);
      isMaximized = true;
      return;
    }
    glfwRestoreWindow(window);
    isMaximized = false;

  }

  void Window::SetPositionOnCenter()
  {
    auto monitor = glfwGetPrimaryMonitor();
    auto videoMode = glfwGetVideoMode(monitor);
    auto size = GetSize();
    SetPosition({videoMode->width / 2 - size[0] / 2, videoMode->height / 2 - size[1] / 2});
  }

  void Window::SetTitle(const std::string &title)
  {
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
  }
}
