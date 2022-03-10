#pragma once

#include "Engine/Module.hpp"
#include <GLFW/glfw3.h>
#include <array>
#include <bits/stdint-intn.h>
#include <Utils/Delegate.hpp>

struct GLFWwindow;

namespace mtEngine {
  enum class InputAction : int32_t {
    Release = 0,
    Press = 1,
    Repeat = 2
  };

  enum class InputMod : int32_t {
    None = 0,
    Shift = 1,
    Control = 2,
    Alt = 4,
    Super = 8
  };

  class Window : public Module::Registrar<Window> {
    inline static const bool Registered = Register(Stage::Pre);
    public:
      Window();
      ~Window();

      void Update() override;
      GLFWwindow *GetWindow() {return window;}

      Delegate<void()> &OnClose() { return onClose; }

    private:
      GLFWwindow *window = nullptr;
      std::array<int, 2> size = {1024, 768};
      friend void CallbackFramebufferSize(GLFWwindow *window, int32_t width, int32_t height);
      friend void CallbackWindowClose(GLFWwindow *window);

      Delegate<void()> onClose;
  };
}
