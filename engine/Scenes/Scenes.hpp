#pragma once

#include <memory>
#include "Engine/Module.hpp"
#include "Scene.hpp"

namespace mtEngine {
  class Scenes: public Module::Registrar<Scenes>
  {
    inline static const bool Registered = Register(Stage::Normal);
    public:
      Scenes();

      void Update() override;

      Scene *GetScene() const { return scene.get(); }

      void SetScene(std::unique_ptr<Scene> &&scene) { this->scene = std::move(scene); }

    private:
      std::unique_ptr<Scene> scene;
  };
}
