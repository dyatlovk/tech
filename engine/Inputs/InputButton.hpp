#pragma once

#include "Devices/Window.hpp"
#include "Utils/Delegate.hpp"
#include "Utils/Factory.hpp"

namespace mtEngine {
  class InputButton : public Factory<InputButton>,  public virtual Observer {
    public:
      virtual ~InputButton() = default;

      virtual bool IsDown() const { return false; };

      bool WasDown()
      {
        auto stillDown = wasDown && IsDown();
        wasDown = IsDown();
        return wasDown == !stillDown;
      }
      Delegate<void(InputAction, InputMod)> &OnButton() { return onButton; }
    
    private:
      bool wasDown = false;
    protected:
      Delegate<void(InputAction, InputMod)> onButton;
  };
}
