#include "World.hpp"

namespace Game
{
  World::World() = default;

  World::~World() = default;

  void World::Start() { gui = dynamic_cast<GameGui *>(Gui::Get()->GetGui()); }

  void World::BeforeUpdate() {}

  void World::Update() { gui->Help(true); }

  void World::AfterUpdate() {}

  void World::Shutdown() { gui = nullptr; }
} // namespace Game
