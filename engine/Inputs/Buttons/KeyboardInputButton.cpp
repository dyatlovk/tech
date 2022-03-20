#include "KeyboardInputButton.hpp"
#include "Inputs/Input.hpp"
#include "States/States.hpp"

namespace  mtEngine {
  KeyboardInputButton::KeyboardInputButton(Key key, const std::string &sectionName): 
    key(key),
    section(sectionName)
  {
    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if (this->key == key) {
        onButton(action, mods);
        return;
      }
    });
  }

  bool KeyboardInputButton::IsDown() const {
    return (Keyboard::Get()->GetKey(key) != InputAction::Release);
  }
}
