#include "World.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start() {  
    gui = std::make_unique<WorldGui>();
  }

  void World::BeforeUpdate() {}

  void World::Update() {
    gui->Window();
  }

  void World::AfterUpdate() {}

  void World::Shutdown() { 
    gui = nullptr;
  }
} // namespace Game
