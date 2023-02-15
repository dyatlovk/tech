#include "Events.hpp"

#include "Engine/Engine.hpp"

namespace mtEngine
{
  Events *Events::Instance = nullptr;

  Events::Events()
      : started(false)
  {
    Instance = this;
  }

  Events::~Events() = default;

  // ---------------------------------------------------------------------------
  auto Events::Init() -> std::unique_ptr<Events>
  {
    auto s = std::make_unique<Events>();

    return s;
  }

  // ---------------------------------------------------------------------------
  auto Events::GetCallBackList() -> eventpp::CallbackList<void()> *
  {
    return &mainLoopTasks;
  }

  // ---------------------------------------------------------------------------
  auto Events::RunTasks() -> void
  {
    std::thread trd(&Events::RunLoop, this);
    trd.detach();
  }

  //////////////////////////////////////////////////////////////////////////////
  // PRIVATE
  //////////////////////////////////////////////////////////////////////////////

  // ---------------------------------------------------------------------------
  auto Events::RunLoop() -> void
  {
    while (Engine::Get()->IsRunning())
    {
      mainLoopTasks();
    }
  }
} // namespace mtEngine
