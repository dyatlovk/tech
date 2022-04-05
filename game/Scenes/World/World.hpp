#pragma once

#include "Gui/WorldGui.hpp"
#include "Gui/Layout.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/Scenes.hpp"

using namespace mtEngine;

namespace Game
{
  class World : public Scene
  {
  public:
    constexpr static std::string_view NAME = "world";

    World();
    ~World();

    void Start() override;
    void BeforeUpdate() override;
    void Update() override;
    void AfterUpdate() override;

    bool IsPaused() const override { return false; }

    void Shutdown() override;
    std::string GetName() const override { return std::string(NAME); };

  private:
    bool show_inv = false;

  private:
    std::unique_ptr<WorldGui> gui;
    std::unique_ptr<WorldLayout> layout;
  };
} // namespace Game
