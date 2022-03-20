#pragma once

#include "Engine/CVars.hpp"
#include "Engine/Engine.hpp"

namespace mtEngine {
  class Commands : public NonCopyable
  {
    public:
      Commands()
      {
        Register();
      };
      
      void Register()
      {
        CVars::Get()->Add("quit", []() {
            Engine::Get()->RequestClose();
        }, "Quit app");
        
        CVars::Get()->Add("help", []() {
          PLOGD << "help test";
        }, "Vars list");
      }
  };
}
