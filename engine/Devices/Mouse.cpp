#include <Devices/Mouse.hpp>

namespace mtEngine
{
  void CallbackPosition(GLFWwindow *window, double xpos, double ypos)
  {
    Mouse::Get()->onPositionEvent(xpos, ypos);
  }

  void CallbackButton(GLFWwindow *window, int button, int action, int mods)
  {

  }

  void CallbackScroll(GLFWwindow *window, double xoffset, double yoffset)
  {
    Mouse::Get()->onScrollEvent(xoffset, yoffset);
  }

  Mouse::Mouse()
  {
    glfwSetCursorPosCallback(Window::Get()->GetWindow(), CallbackPosition);
    glfwSetMouseButtonCallback(Window::Get()->GetWindow(), CallbackButton);
    glfwSetScrollCallback(Window::Get()->GetWindow(), CallbackScroll);
  }

  void Mouse::Update() {

  }
} // namespace mtEngine
