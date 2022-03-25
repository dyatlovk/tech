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
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;
    CVars::Get()->Add("global", "quit", {}, "App quit", "command", [](CVarParam &args, Input &input, bool &isValid) {
        Engine::Get()->RequestClose();
    }, "command", true);

    CVars::Get()->Add("global", "clear", {}, "Clear console", "global clear", [](CVarParam &args, Input &input, bool &isValid) {
      Log::Get()->Clear();
      isValid = true;
    }, "command", true);

    CVars::Get()->Add("global", "version", {}, "Engine version info", "engine version", [](CVarParam &args, Input &input, bool &isValid) {
      auto const build = IniParser::Get()->Read("Build", "Build");
      auto const date = IniParser::Get()->Read("Build", "CompileDate");
      PLOGD << "=============================";
      PLOGD << "Engine: " << VERSION << "." << COMPILED_COMMIT_HASH;
      PLOGD << "Build: " << build << " (" << date << ")";
      PLOGD << "Compiler: " << COMPILED_COMPILER << " [" << COMPILED_GENERATOR << "]";
      PLOGD << "System: " << COMPILED_SYSTEM;
      PLOGD << "=============================";
      isValid = true;
    }, "command", true);
  }
} // namespace mtEngine
