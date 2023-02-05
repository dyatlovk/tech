#pragma once

#include <Devices/Mouse.hpp>
#include <Guis/Console.hpp>
#include <Guis/Gui.hpp>
#include <Scenes/Scenes.hpp>

namespace World::Events
{
  using namespace mtEngine;

  inline auto onConsoleShow() -> void
  {
    Gui::Get()->GetConsole()->OnShow().Add(
        []()
        {
          Mouse::Get()->ShowCursor();
          auto camera = mtEngine::Scenes::Get()->GetCamera();
          if (camera)
            camera->SetMoveIsPaused(true);
        });
  }

  inline auto onConsoleClose() -> void
  {
    Gui::Get()->GetConsole()->OnClose().Add(
        []()
        {
          Mouse::Get()->HideCursor();
          auto camera = mtEngine::Scenes::Get()->GetCamera();
          if (camera)
            camera->SetMoveIsPaused(false);
          Mouse::Get()->SetCenterPosition();
        });
  }
} // namespace World::Events
