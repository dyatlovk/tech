#pragma once

#include <Devices/Window.hpp>

namespace mtEngine
{

  struct MousePosition;

  class Mouse : public Module::Registrar<Mouse>
  {
    inline static const bool Registered = Register(Stage::Pre, Requires<Window>());

  public:
    Mouse();
    virtual ~Mouse() = default;

    void Update() override;

    struct MousePosition {
      double x, y;
    } pos;

    const MousePosition *GetPosition() { return &pos; }

    void HideCursor() { glfwSetInputMode(Window::Get()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); };
    void ShowCursor() { glfwSetInputMode(Window::Get()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); };
    void SetCenterPosition() {
      pos.x = (double) Window::Get()->GetSize()[0] / 2;
      pos.y = (double) Window::Get()->GetSize()[1] / 2;
    }

    Delegate<void(double, double)> onPositionEvent;
    Delegate<void(double, double)> onScrollEvent;

  private:
    double xpos, ypos;
  };
} // namespace mtEngine
