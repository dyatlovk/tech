#pragma once

#include "Inputs/InputButton.hpp"
#include "Devices/Keyboard.hpp"
#include "Utils/Factory.hpp"

namespace mtEngine {
  class KeyboardInputButton : public InputButton::Registrar<KeyboardInputButton> {
    inline static const bool Registered = Register("keyboard");
    public:
      explicit KeyboardInputButton(Key key = Key::Unknown, const std::string &sectionName = "Global");

      Key GetKey() const { return key; };

      bool IsDown() const override;

    private:
      Key key;
      std::string section;
  };
}
