#pragma once

#include <typeindex>

#include "Utils/NonCopyable.hpp"

namespace mtEngine
{
  class Resource : public NonCopyable
  {
  public:
    Resource() = default;

    virtual ~Resource() = default;

    [[nodiscard]] virtual std::type_index GetTypeIndex() const = 0;
  };
} // namespace mtEngine
