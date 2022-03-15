#include "KeyboardInputButton.hpp"
#include "Inputs/Input.hpp"

namespace  mtEngine {
  KeyboardInputButton::KeyboardInputButton(Key key, const std::string &sectionName): 
    key(key),
    section(sectionName)
  {
    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if(section == "Global") Input::Get()->EnableScheme(true);
      if (this->key == key && Input::Get()->IsSchemeEnabled()) {
        onButton(action, mods);
        return;
      }
    });
  }

  bool KeyboardInputButton::IsDown() const {
    return (Keyboard::Get()->GetKey(key) != InputAction::Release);
  }
}
