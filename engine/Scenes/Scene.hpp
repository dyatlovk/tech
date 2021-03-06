#pragma once

#include <string>

namespace mtEngine {
  class Scene {
    friend class Scenes;
    public:
      Scene() {};

      virtual ~Scene() = default;

      virtual void Start() = 0;
      virtual void Update() = 0;
      virtual void BeforeUpdate() {};
      virtual void AfterUpdate() {};
      virtual bool IsPaused() const = 0;
      virtual void Shutdown() = 0;
      virtual std::string GetName() const = 0;

    private:
      bool started = false;
  };
}
