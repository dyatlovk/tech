#pragma once

#include <cmath>
#include <bitset>
#include <memory>

#include "Utils/NonCopyable.hpp"
#include "Module.hpp"
#include "App.hpp"
#include "Log.hpp"

namespace mtEngine {

  /**
   * @brief Main class for Acid, manages modules and updates. After creating your Engine object call {@link Engine#Run} to start.
   */
  class Engine : NonCopyable {
    public:
      /**
       * Gets the engines instance.
       * @return The current engine instance.
       */
      static Engine *Get() { return Instance; }

      /**
       * Carries out the setup for basic engine components and the engine. Call {@link Engine#Run} after creating a instance.
       * @param argv0 The first argument passed to main.
       * @param moduleFilter A filter for blacklisting/whitelisting modules.
       */
      explicit Engine(std::string argv0, ModuleFilter &&moduleFilter = {});
      ~Engine();

      /**
       * The update function for the updater.
       * @return {@code EXIT_SUCCESS} or {@code EXIT_FAILURE}
       */
      int32_t Run();

      /**
       * Gets the first argument passed to main.
       * @return The first argument passed to main.
       */
      const std::string &GetArgv0() const { return argv0; };

      /**
       * Gets the engine's version.
       * @return The engine's version.
       */
      const Version &GetVersion() const { return version; }

      /**
       * Gets the current application.
       * @return The renderer manager.
       */
      App *GetApp() const { return app.get(); }

      /**
       * Sets the current application to a new application.
       * @param app The new application.
       */
      void SetApp(std::unique_ptr<App> &&app) { this->app = std::move(app); }

      /**
       * Gets the fps limit.
       * @return The frame per second limit.
       */
      float GetFpsLimit() const { return fpsLimit; }

      /**
       * Sets the fps limit. -1 disables limits.
       * @param fpsLimit The new frame per second limit.
       */
      void SetFpsLimit(float fpsLimit) { this->fpsLimit = fpsLimit; }

      /**
       * Gets if the engine is running.
       * @return If the engine is running.
       */
      bool IsRunning() const { return running; }

      /**
       * Requests the engine to stop the game-loop.
       */
      void RequestClose() { running = false; }

      std::shared_ptr<Log> GetLogger() { return logger; };

    private:
      void UpdateStage(Module::Stage stage);
      void PostUpdate();

      static Engine *Instance;

      std::string argv0;
      Version version;

      std::unique_ptr<App> app;

      std::multimap<Module::StageIndex, std::unique_ptr<Module>> modules;

      float fpsLimit;
      bool running;
      std::shared_ptr<Log> logger;
  };
}
