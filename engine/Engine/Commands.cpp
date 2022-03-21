#include "Commands.hpp"
#include <string>
#include "Engine.hpp"

namespace mtEngine
{
  Commands *Commands::Instance = nullptr;
  
  Commands::Commands()
  {
    Instance = this;
    PLOGD << "commands start";
  };
  
  Commands::~Commands() = default;

  void Commands::Register()
  {
    CVars::Get()->Add(
        "quit", []() { Engine::Get()->RequestClose(); }, "Quit app");

    CVars::Get()->Add(
        "help", []() { PLOGD << "help test"; }, "Vars list");

    CVars::Get()->Add<std::string>("debug", "0", "0", "Switch debug mode");
    CVars::Get()->Add("version", [](){
      PLOGD << "===========";
      PLOGD << "Engine: " << VERSION << "." << COMPILED_COMMIT_HASH;
      PLOGD << "Build: " << BUILD_NO << " (" << COMPILE_TIME << ")";
      PLOGD << "Compiler: " << COMPILED_COMPILER << " [" << COMPILED_GENERATOR << "]";
      PLOGD << "System: " << COMPILED_SYSTEM;
      PLOGD << "===========";
    }, "Engine version");
  }
} // namespace mtEngine
