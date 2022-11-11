#include "Window.hpp"
#include "Engine/Engine.hpp"
#include <Devices/Mouse.hpp>

namespace mtEngine {
  void CallbackFrameBufferSize(GLFWwindow *window, int32_t width, int32_t height)
  {
    Window::Get()->size = {width, height};
    glViewport(0, 0, width, height);
  }

  void CallbackWindowClose(GLFWwindow *window)
  {
    Engine::Get()->RequestClose();
    Window::Get()->onClose();
  }

  void CallbackWindowSize(GLFWwindow *window, int32_t width, int32_t height)
  {
    if (width <= 0 || height <= 0) return;
    Window::Get()->size = {width, height};
  }

  void CallbackWindowFocus(GLFWwindow *window, int focused)
  {
    if (!focused) {
      Mouse::Get()->ShowCursor();
    }
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

    if(glewInit() != GLEW_OK) throw std::runtime_error("glewInit failed");

    glfwSetWindowCloseCallback(window, CallbackWindowClose);
    glfwSetFramebufferSizeCallback(window, CallbackFrameBufferSize);
    glfwSetWindowSizeCallback(window, CallbackWindowSize);
    glfwSetWindowFocusCallback(window, CallbackWindowFocus);

    if (glfwRawMouseMotionSupported())
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    std::string maximizedFlag = std::to_string(isMaximized);
    CVars::Get()->Add("window", "maximized", {maximizedFlag}, "Window swtich maximized", "window maximized <1|0>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.empty()) {
        isValid = false;
        return;
      }
      if(input.at(0) != "1" && input.at(0) != "0") {
        isValid = false;
        return;
      }

      int flag = std::stoi(input.at(0));

      if(flag == 1) {
        isMaximized = true;
      } else {
        isMaximized = false;
      }

      Maximize(flag);
      isValid = true;
    });

    CVars::Get()->Add("window", "title", {title}, "Window set title", "window title <char>", [this](CVarParam &args, Input &input, bool &isValid) {
      if(input.empty()) {
        isValid = false;
        return;
      }
      SetTitle(input.at(0));
      isValid = true;
    });
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
  }

  void Window::SetFullScreen(bool fullScreen)
  {
    this->fullScreen = fullScreen;
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
    SetPosition({videoMode->width / 2 - size.front() / 2, videoMode->height / 2 - size.back() / 2});
  }

  void Window::SetTitle(const std::string &title)
  {
    this->title = title;
    glfwSetWindowTitle(window, title.c_str());
  }

  void Window::SwapBuffers()
  {
    glfwSwapBuffers(window);
  }

  void Window::ActivateContext()
  {
    glfwMakeContextCurrent(window);
  }

  float Window::GetAspectRatio()
  {
    return (float) this->size.front() / (float) this->size.back();
  }
}
