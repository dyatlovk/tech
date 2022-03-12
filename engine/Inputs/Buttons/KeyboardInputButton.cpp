#include "KeyboardInputButton.hpp"

namespace  mtEngine {
  KeyboardInputButton::KeyboardInputButton(Key key): key(key)
  {
    Keyboard::Get()->OnKey().Add([this](Key key, InputAction action, InputMod mods) {
      if (this->key == key) {
        onButton(action, mods);
      }
    });
  }

  bool KeyboardInputButton::IsDown() const {
    return (Keyboard::Get()->GetKey(key) != InputAction::Release);
  }
}
