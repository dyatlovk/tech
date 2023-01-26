#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Utils/ThreadPool.hpp"

namespace Game
{
  using namespace mtEngine;

  class AppCommands
  {
  public:
    AppCommands();

    ~AppCommands();

    auto LoadScene() -> void;

    auto ResourceLoad() -> void;

    auto ResourceInfo() -> void;

    auto ResourcesGet() -> void;

    auto ResourceRemove() -> void;

  private:
    using CVarParam = std::vector<std::string>;
    using Input = std::vector<std::string>;

    ThreadPool *threadPool;
  };
} // namespace Game
