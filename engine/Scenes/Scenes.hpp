#pragma once

#include <memory>
#include "Engine/Module.hpp"
#include "Scene.hpp"
#include "Engine/Log.hpp"

namespace mtEngine {
  class Scenes: public Module::Registrar<Scenes>
  {
    inline static const bool Registered = Register(Stage::Normal);
    public:
      Scenes();

      void Update() override;

      Scene *GetScene() const { return scene.get(); }

      void SetScene(std::unique_ptr<Scene> &&scene) {
        if(!scene) {
          this->scene = nullptr;
          return;
        }

        if(this->scene) this->scene->Shutdown();
        
        // remove previous scene;
        this->scene = nullptr;

        // set new scene
        this->scene = std::move(scene);
      }

      void Reload(std::unique_ptr<Scene> &&scene)
      {
        if(this->scene->GetName() == scene->GetName()) return;
        SetScene(std::move(scene));
      }

      void Shutdown() override;

    private:
      std::unique_ptr<Scene> scene = nullptr;
  };
}
