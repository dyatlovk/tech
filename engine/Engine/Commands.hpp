#pragma once

#include "CVars.hpp"

namespace mtEngine
{
  class Commands : public NonCopyable
  {
  public:
    Commands();
    ~Commands();

    static std::unique_ptr<Commands> Init()
    {
      auto com = std::make_unique<Commands>();
      com->Register();

      return com;
    }

  private:
    void Register();
    static Commands *Instance;
  };
} // namespace mtEngine
