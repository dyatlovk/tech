#include "InputScheme.hpp"
#include "Inputs/InputButton.hpp"

namespace mtEngine {
  InputScheme::InputScheme() = default;

  InputButton *InputScheme::GetButton(const std::string &name)
  {
    auto it = buttons.find(name);
    if (it == buttons.end()) {
      it = buttons.emplace(name, std::make_unique<InputButton>()).first;
    }
    return it->second.get();
  }

  InputButton *InputScheme::AddButton(const std::string &name, std::unique_ptr<InputButton> &&button) {
    return buttons.emplace(name, std::move(button)).first->second.get();
  }

  void InputScheme::RemoveButton(const std::string &name) {
    if (auto it = buttons.find(name); it != buttons.end())
      buttons.erase(it);
  }

  void InputScheme::MoveDelegateOwnership(InputScheme *other) {
    if (!other) return;
    // Move all delegate functions except those owned internally by the axis or button.
    for (auto &[buttonName, button] : other->buttons)
      GetButton(buttonName)->OnButton().MoveFunctions(button->OnButton(), {button->valid});
  }
}
