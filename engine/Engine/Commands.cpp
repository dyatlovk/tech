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
  }
} // namespace mtEngine
