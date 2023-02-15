#pragma once

#include "Engine/Engine.hpp"
#include "Engine/Events.hpp"
#include "Guis/Gui.hpp"
#include "third_party/eventpp/eventqueue.h"

namespace Game
{
  namespace GUI
  {
    enum class Events : int
    {
      OnStatsToggle = 1,
    };
  } // namespace GUI

  class GameGui : public eventpp::EventQueue<GUI::Events, void()>
  {
  public:
    GameGui();

    ~GameGui();

    auto static Get() -> GameGui * { return Instance; };

    auto static Init() -> std::unique_ptr<GameGui>;

    void Update();

    void Stats();

    void Debug();

  private:
    bool showStats = true;
    bool showUIDebug = false;
    static GameGui *Instance;
  };
} // namespace Game
