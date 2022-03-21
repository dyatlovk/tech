#pragma once

#include <memory>

#include "Config.hpp"
#include "Utils/NonCopyable.hpp"
#include "third_party/inicpp/ini.h"

namespace mtEngine
{
  class IniParser : public NonCopyable
  {
  public:
    IniParser();

    ~IniParser();

    static IniParser *Get() { return Instance; }

    static std::unique_ptr<IniParser> Init()
    {
      return std::make_unique<IniParser>();
    }

    std::string Read(const std::string &section, const std::string &value)
    {
      std::string result;
      try
      {
        result = reader.Get<std::string>(section, value);
      }
      catch (const std::runtime_error &)
      {
        result = "";
      }
      return result;
    };

  private:
    static IniParser *Instance;
    inih::INIReader reader;
  };
} // namespace mtEngine
