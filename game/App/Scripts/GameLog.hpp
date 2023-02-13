#pragma once

#include <string>

#include "third_party/plog/Log.h"
namespace Game
{
  class GameLog
  {
  public:
    GameLog(){};
    ~GameLog(){};

    auto info(const std::string &msg) -> void { PLOGI << msg; }
    auto error(const std::string &msg) -> void { PLOGE << msg; }
    auto debug(const std::string &msg) -> void { PLOGD << msg; }
    auto fatal(const std::string &msg) -> void { PLOGF << msg; }
  };
} // namespace Game
