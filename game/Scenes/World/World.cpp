#include "World.hpp"
#include "Guis/Gui.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start() {  
    gui = std::make_unique<WorldGui>();
    layout = std::make_unique<WorldLayout>();
  }

  void World::BeforeUpdate() {}

  void World::Update() {
    gui->PlayerInfoDock();
  }

  void World::AfterUpdate() {}

  void World::Shutdown() { 
    gui = nullptr;
    layout = nullptr;
  }
} // namespace Game
