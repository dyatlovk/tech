#include "GameRender.hpp"
#include "Config.hpp"
#include "Graphics/Texture.hpp"

namespace Game {
  std::unique_ptr<Texture> texture;
 
  GameRender::GameRender()
  {

  }

  GameRender::~GameRender()
  {
    PLOGD << "app render destruct";
  }

  void GameRender::Start()
  {
    GameUI = std::make_unique<GameGui>();
    PLOGD << "app render start";
    texture = std::make_unique<Texture>();
    const std::string p(RESOURCES);
    bool ret = texture->LoadTextureFromFile(p + "/Game/textures/bg.jpg", &image_texture, &image_width, &image_height);

    Keyboard::Get()->OnKey().Add([&](Key key, InputAction action, InputMod mods) {
      if(States::Get()->Current() == EnumStates::Console) return;
      if(InputAction::Press == action && key == Key::Tab) {
        showHelp = !showHelp;
      }
    });
  }

  void GameRender::Update()
  {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoBringToFrontOnFocus;
    auto viewport = ImGui::GetMainViewport()->Size;
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(viewport.x, viewport.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f, 0.f });
    ImGui::Begin("OpenGL Texture Text", nullptr, window_flags);
    ImGui::Image((void*)(intptr_t)image_texture, ImVec2(image_width, image_height));
    ImGui::PopStyleVar();
    ImGui::End();

    GameUI->Help(showHelp);
    GameUI->Inventory();
    GameUI->Info();
  }
}
