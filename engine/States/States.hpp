#pragma once

#include "Devices/Keyboard.hpp"
#include "Engine/Module.hpp"
#include "States/EnumStates.hpp"
#include <string>
#include <iostream>

namespace mtEngine {
  class States : public Module::Registrar<States> {
    inline static const bool Registered = Register(Stage::Pre, Requires<Keyboard>());
    public:
      States();

      void Update() override;

      void Set(int state);

      static std::string ToString(int state)
      {
        if(state == EnumStates::Player) {
          return "Player";
        }

        if(state == EnumStates::GUI) {
          return "GUI";
        }

        if(state == EnumStates::Default) {
          return "Default";
        }

        return "Default";
      }
      
      int Current()
      {
        return current;
      }
      
      Delegate<void(int)> &OnState() { return onState; }

    private:
      int current;
      Delegate<void(int)> onState;
  };
}
