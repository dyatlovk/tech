#pragma once

#include "States/States.hpp"

namespace Game {
  class GameStates 
  {
    public:
      enum {
        Player  = 0,
        PauseMenu = 1,
        MainMenu = 2,
        Inventory = 3,
      };
      
      static std::string ToString(int state)
      {
        if(state == GameStates::Player) {
          return "Player";
        }
        
        if(state == GameStates::PauseMenu) {
          return "PauseMenu";
        }
        
        if(state == GameStates::MainMenu) {
          return "MainMenu";
        }
        
        if(state == GameStates::Inventory) {
          return "Inventory";
        }

        return "Default";
      }
  };
}
