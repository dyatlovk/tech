#ifndef EDITOR_APP_H
#define EDITOR_APP_H

#include "Engine/App.hpp"

namespace Editor {
  class EditorApp: public mtEngine::App {
    public:
      EditorApp();
      ~EditorApp();

      void Start() override;
      void Update() override;
  };
}

#endif // !APP_H
