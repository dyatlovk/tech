#pragma once

#include <memory>

#include "FPSCamera.hpp"
#include "Gui/Grid.hpp"
#include "Gui/Notify.hpp"
#include "Gui/WorldGui.hpp"
#include "Models/Model.hpp"
#include "Scenes/Scene.hpp"
#include "Scenes/Scenes.hpp"
#include "Scenes/World/Vars/Entities.hpp"

using namespace mtEngine;

namespace Game
{
  class World : public Scene
  {
  public:
    constexpr static std::string_view NAME = "world";

    World();
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
    std::unique_ptr<Notify> notify;
    std::unique_ptr<Model> model;
    std::unique_ptr<Grid> m_grid;
    std::unique_ptr<Entities> m_var_entities;
  };
} // namespace Game
