#pragma once

#include "Devices/Keyboard.hpp"
#include "Utils/NonCopyable.hpp"
#include "InputButton.hpp"

#include <map>
#include <memory>
#include <string>

namespace mtEngine {
  class InputScheme : NonCopyable {
    friend class Input;
    public:
      using ButtonMap = std::map<std::string, std::unique_ptr<InputButton>>;
      InputScheme();

      InputButton *GetButton(const std::string &name);
      InputButton *AddButton(const std::string &name, std::unique_ptr<InputButton> &&button);
      void RemoveButton(const std::string &name);

    private:
      ButtonMap buttons;

      void MoveDelegateOwnership(InputScheme *other);
  };
}
