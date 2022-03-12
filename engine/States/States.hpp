#pragma once

#include "Devices/Keyboard.hpp"
#include "Engine/Module.hpp"
#include <string>
#include <iostream>

namespace mtEngine {
  enum class State : int {
    Default = 0,
    Player  = 1,
    GUI     = 2,
  };

  class States : public Module::Registrar<States> {
    inline static const bool Registered = Register(Stage::Pre, Requires<Keyboard>());
    public:
      States();

      void Update() override;

      void Set(State state);

      static std::string ToString(State state)
      {
        switch (state) {
          case State::Player:
            return "Player";
          case State::GUI:
            return "GUI";
          default:
            return "Default";
            break;
        }
      }
      
      State Current()
      {
        return current;
      }
      
      Delegate<void(State)> &OnState() { return onState; }

    private:
      State current;
      Delegate<void(State)> onState;
  };
}
