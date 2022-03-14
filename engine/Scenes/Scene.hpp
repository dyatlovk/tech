#pragma once

namespace mtEngine {
  class Scene {
    friend class Scenes;
    public:
      Scene() {};

      virtual ~Scene() = default;

      virtual void Start() = 0;
      virtual void Update() = 0;
      virtual bool IsPaused() const = 0;

    private:
      bool started = false;
  };
}
