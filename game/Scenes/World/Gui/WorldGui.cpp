#include "WorldGui.hpp"
#include "../../MainMenu/MainMenu.hpp"

namespace Game
{
    WorldGui::WorldGui() = default;

    void WorldGui::Window()
    {
      ImGui::Begin("##world_window");
      if (ImGui::Button("MainMenu")) {
        Scenes::Get()->SetScene(std::make_unique<MainMenu>());
      }
      ImGui::End();
    }
} // namespace Game
