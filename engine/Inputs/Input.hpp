#pragma once

#include "Devices/Keyboard.hpp"
#include "InputButton.hpp"
#include "Buttons/KeyboardInputButton.hpp"
#include "Utils/Delegate.hpp"
#include "Engine/Engine.hpp"
#include "third_party/inicpp/ini.h"
#include <filesystem>

namespace mtEngine {
  class Input : public Module::Registrar<Input> {
    inline static const bool Registered = Register(Stage::Normal, Requires<Keyboard>());
    public:
      using ButtonMap = std::map<std::string, std::unique_ptr<InputButton>>;

      Input();

      void Update() override;

      void LoadConfig(const std::filesystem::path &filename);
      void EnableScheme(const std::string &section);
      bool IsSchemeEnabled(const std::string &section);
      std::string &GetCurrentScheme() const {
        return const_cast<std::string&>(section);
      };

      InputButton *GetButton(const std::string &section, const std::string &name);
      Delegate<void(InputAction, InputMod)> &OnButton(const std::string &name) { return onClick; };

    private:
      inih::INIReader maps_m;
      ButtonMap buttons;
      Delegate<void(InputAction, InputMod)> onClick;
      bool isSchemeEnabled = true;
      std::string section;
  };
}
