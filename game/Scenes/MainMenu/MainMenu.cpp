#include "MainMenu.hpp"

namespace Game
{
  MainMenu::MainMenu() = default;

  MainMenu::~MainMenu() = default;

  void MainMenu::Start() {
    gui = std::make_unique<MenuGui>();
  }

  void MainMenu::BeforeUpdate() {}

  void MainMenu::Update() {
    gui->RenderList();
  }

  void MainMenu::AfterUpdate() {}

  void MainMenu::Shutdown() {
    gui = nullptr;
  }

} // namespace Game
