#include "Input.hpp"

namespace mtEngine {
  Input::Input() { };

  void Input::LoadScheme(const std::filesystem::path &filename)
  {
    maps_m = {filename};
  }

  void Input::Update() { }

  InputButton *Input::GetButton(const std::string &section, const std::string &name) {
    const auto& keyFound = maps_m.Get<std::string>(section, name);
    auto it = buttons.find(section + name);
    if (it == buttons.end()) {
      auto key = Keyboard::FromString(keyFound);
      it = buttons.emplace(section + name, std::make_unique<KeyboardInputButton>(key, section)).first;
    }
    return it->second.get();
  }
}
