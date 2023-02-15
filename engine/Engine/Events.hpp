#pragma once

#include "Utils/NonCopyable.hpp"
#include "third_party/eventpp/callbacklist.h"

namespace mtEngine
{
  class Events : public mtEngine::NonCopyable
  {
  public:
    Events();

    ~Events() override;

    // ---------------------------------------------------------------------------
    // Run task callback in loop
    auto RunTasks() -> void;

    // ---------------------------------------------------------------------------
    auto GetCallBackList() -> eventpp::CallbackList<void()> *;

    // ---------------------------------------------------------------------------
    // Get instance
    auto static Get() -> Events * { return Instance; };

    // ---------------------------------------------------------------------------
    // static constructor
    auto static Init() -> std::unique_ptr<Events>;

    // ---------------------------------------------------------------------------
    // is task loop started
    bool started;

  private:
    auto RunLoop() -> void;
    eventpp::CallbackList<void()> mainLoopTasks;
    static Events *Instance;
  };
} // namespace mtEngine
