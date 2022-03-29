#pragma once

#include "Graphics/Texture.hpp"
#include "Gui/MenuGui.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/Scenes.hpp"
#include "Graphics/Renderer.hpp"

using namespace mtEngine;

namespace Game
{
  class MainMenu : public Scene
  {
  public:
    constexpr static std::string_view NAME = "main_menu";

    MainMenu();
    ~MainMenu();

    void Start() override;
    void BeforeUpdate() override;
    void Update() override;
    void AfterUpdate() override;
    bool IsPaused() const override { return false; }
    void Shutdown() override;
    std::string GetName() const override { return std::string(NAME); };

  private:
    std::unique_ptr<MenuGui> gui;
    int tex_width = 0;
    int tex_height = 0;
    GLuint bg_image = 0;
    std::unique_ptr<Texture> bg_texture;
  };
} // namespace Game
