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
    Gui::Get()->StyleDocking();
    layout->Create();
    gui->Window();
    gui->PlayerInfoDock();
    // gui->Item();
  }

  void World::AfterUpdate() {}

  void World::Shutdown() { 
    gui = nullptr;
    layout = nullptr;
  }
} // namespace Game
