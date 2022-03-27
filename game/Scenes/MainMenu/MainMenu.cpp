#include "MainMenu.hpp"

namespace Game
{
  MainMenu::MainMenu() = default;

  MainMenu::~MainMenu() = default;

  void MainMenu::Start()
  {
    gui = dynamic_cast<GameGui *>(Gui::Get()->GetGui());
  }

  void MainMenu::BeforeUpdate() {}

  void MainMenu::Update()
  {
    gui->Inventory();
    gui->Info();
  }

  void MainMenu::AfterUpdate() {}

  void MainMenu::Shutdown() { gui = nullptr; }

} // namespace Game
