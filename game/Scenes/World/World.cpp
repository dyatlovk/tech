#include "World.hpp"

#include "Guis/Gui.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start()
  {
    gui = std::make_unique<WorldGui>();
    layout = std::make_unique<WorldLayout>();
    Keyboard::Get()->OnKey().Add([this](Key key, InputAction action, InputMod mods) {
      if(key == Key::I && action == InputAction::Press) {
        show_inv = !show_inv;
      }
    });
  }

  void World::BeforeUpdate() {}

  void World::Update()
  {
    gui->PlayerInfoDock();
    if(show_inv) gui->Inventory();
  }

  void World::AfterUpdate() {}

  void World::Shutdown()
  {
    gui = nullptr;
    layout = nullptr;
  }
} // namespace Game
