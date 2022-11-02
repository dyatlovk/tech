#pragma once

#include <memory>
#include <string>

#include "Scenes/Camera.hpp"

namespace mtEngine
{
  class Scene
  {
    friend class Scenes;

  public:
    Scene(std::unique_ptr<Camera> &&camera)
        : camera(std::move(camera)){};

    virtual ~Scene() = default;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void BeforeUpdate(){};
    virtual void AfterUpdate(){};
    virtual bool IsPaused() const = 0;
    virtual void Shutdown() = 0;
    virtual std::string GetName() const = 0;

    Camera *GetCamera() const { return camera.get(); }
    void SetCamera(Camera *camera) { this->camera.reset(camera); }

  private:
    bool started = false;
    std::unique_ptr<Camera> camera;
  };
} // namespace mtEngine
