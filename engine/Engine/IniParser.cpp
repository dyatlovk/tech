#include "IniParser.hpp"

namespace mtEngine
{
  IniParser *IniParser::Instance = nullptr;
  
  IniParser::IniParser()
  {
    Instance = this;
    std::string p(RESOURCES);
    reader = {p + "/Engine/Settings.ini"};
  }

  IniParser::~IniParser() = default;
} // namespace mtEngine
