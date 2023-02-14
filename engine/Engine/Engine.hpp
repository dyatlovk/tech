#pragma once

#include <bitset>
#include <cmath>
#include <memory>

#include "App.hpp"
#include "CVars.hpp"
#include "Commands.hpp"
#include "Config.hpp"
#include "IniParser.hpp"
#include "Log.hpp"
#include "Maths/ElapsedTime.hpp"
#include "Maths/Time.hpp"
#include "Module.hpp"
#include "Network/Sockets/ServerSocket.hpp"
#include "Scripts/Lua/LuaBind.hpp"
#include "Utils/NonCopyable.hpp"

namespace mtEngine
{

  class Delta
  {
  public:
    void Update()
    {
      currentFrameTime = Time::Now();
      change = currentFrameTime - lastFrameTime;
      lastFrameTime = currentFrameTime;
    }

    Time currentFrameTime;
    Time lastFrameTime;
    Time change;
  };

  class ChangePerSecond
  {
  public:
    void Update(const Time &time)
    {
      valueTemp++;

      if (std::floor(time.AsSeconds()) > std::floor(valueTime.AsSeconds()))
      {
        value = valueTemp;
        valueTemp = 0;
      }

      valueTime = time;
    }

    uint32_t valueTemp = 0, value = 0;
    Time valueTime;
  };

  class Engine : NonCopyable
  {
  public:
    /**
     * Gets the engines instance.
     * @return The current engine instance.
     */
    static Engine *Get() { return Instance; }

    /**
     * Carries out the setup for basic engine components and the engine. Call {@link Engine#Run} after creating a
     * instance.
     * @param argv0 The first argument passed to main.
     * @param moduleFilter A filter for blacklisting/whitelisting modules.
     */
    explicit Engine(std::string argv0, ModuleFilter &&moduleFilter = {});
    ~Engine() override;

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

    const Time &GetDeltaRender() const { return deltaRender.change; }

    const Time &GetDelta() const { return deltaUpdate.change; }

    uint32_t GetFps() const { return fps.value; }

  private:
    void UpdateStage(Module::Stage stage);
    void PreUpdate();
    void PostUpdate();
    void ModuleShutdown();

    static Engine *Instance;

    std::string argv0;
    Version version;

    std::unique_ptr<App> app;

    std::multimap<Module::StageIndex, std::unique_ptr<Module>> modules;

    float fpsLimit;
    bool running;
    std::unique_ptr<Log> log;
    std::unique_ptr<CVars> cvars;
    std::unique_ptr<Commands> commands;
    std::unique_ptr<IniParser> iniParser;
    std::unique_ptr<ServerSocket> server;
    std::unique_ptr<LuaBind> lua;

    Delta deltaUpdate, deltaRender;
    ElapsedTime elapsedUpdate, elapsedRender;
    ChangePerSecond ups, fps;
  };
} // namespace mtEngine
