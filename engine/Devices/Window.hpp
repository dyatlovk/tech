#pragma once

#include "Engine/Module.hpp"
#include <GL/glew.h>
#define GLFW_INCLUDE_GLEXT
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
      ~Window() override;

      void BeforeUpdate() override;
      void Update() override;
      void AfterUpdate() override;

      GLFWwindow *GetWindow() {return window;}

      void SetFullScreen(bool fullScreen);

      void SetPosition(const std::array<int, 2> &pos);

      void SetPositionOnCenter();

      void MaximizeToggle();
      void Maximize(bool state);

      const std::string &GetTitle() const { return title; }

      void SetTitle(const std::string &title);

      const std::array<int, 2> &GetSize() const { return size; }

      void SwapBuffers();

      void ActivateContext();

      float GetAspectRatio();

      Delegate<void()> &OnClose() { return onClose; }
      Delegate<void(std::array<int, 2>)> &OnSize() { return onSize; }

    private:
      GLFWwindow *window = nullptr;
      std::string title{};
      bool fullScreen = false;
      bool isMaximized = false;

      std::array<int, 2> size = {1024, 768};
      friend void CallbackFrameBufferSize(GLFWwindow *window, int32_t width, int32_t height);
      friend void CallbackWindowClose(GLFWwindow *window);
      friend void CallbackWindowSize(GLFWwindow *window, int32_t width, int32_t height);
      friend void CallbackWindowFocus(GLFWwindow *window, int focused);

      Delegate<void()> onClose;
      Delegate<void(std::array<int, 2>)> onSize;
  };
}
