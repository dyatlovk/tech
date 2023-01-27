#include "MainMenu.hpp"
#include "Engine/Engine.hpp"
#include "Scenes/Scene.hpp"

namespace Game
{
  MainMenu::MainMenu(): Scene(nullptr)
  {
    ServerSocket::Get()->emit("scene_name:" + std::string(NAME));
  }

  MainMenu::~MainMenu()
  {
    ResourcesManager::Get()->remove("bg");
    PLOGD << "main menu terminated";
  }

  void MainMenu::Start() {
    Mouse::Get()->ShowCursor();
    gui = std::make_unique<MenuGui>();
    Engine::Get()->GetApp()->GetThreadPool().Enqueue([]() {
      const std::string p(RESOURCES);
      Texture::Create("bg", p + "/Game/textures/Menu/tayga.jpg");
    });
    PLOGD << "main menu started";
  }

  void MainMenu::BeforeUpdate() {
  }

  void MainMenu::Update() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
    window_flags |= ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });
    ImGui::Begin("MainMenu_bg", nullptr, window_flags);
    auto bgImage = ResourcesManager::Get()->find<Texture>("bg");
    if(bgImage) {
      bgImage->Update();
      auto tex = bgImage->GetTexture();
      ImGui::Image((void*)(intptr_t)tex, viewport);
    }
    ImGui::PopStyleVar();
    ImGui::End();

    gui->RenderList();
  }

  void MainMenu::AfterUpdate() {
  }

  void MainMenu::Shutdown() {
    gui = nullptr;
    PLOGD << "main menu shutdown";
  }

} // namespace Game
