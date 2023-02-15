#include "Engine.hpp"

#include "Devices/Window.hpp"

namespace mtEngine
{
  Engine *Engine::Instance = nullptr;

  Engine::Engine(std::string argv0, ModuleFilter &&moduleFilter)
      : argv0(std::move(argv0))
      , version{VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH}
      , fpsLimit(-1.0f)
      , running(true)
  {
    Instance = this;

    log       = Log::Init();
    events    = Events::Init();
    lua       = LuaBind::Init();
    PLOGD << "starting engine...";
    cvars     = CVars::Init();
    commands  = Commands::Init();
    iniParser = IniParser::Init();
    server    = ServerSocket::Init();
    if(!server) exit(1);

    // TODO: Optimize and clean up!
    std::vector<TypeId> created;
    for (;;)
    {
      bool postponed = false;
      for (const auto &[moduleId, moduleTest] : Module::Registry())
      {
        if (std::find(created.begin(), created.end(), moduleId) != created.end())
          continue;
        if (!moduleFilter.Check(moduleId))
          continue;
        bool this_postponed = false;
        for (const auto &requireId : moduleTest.requires)
        {
          if (!moduleFilter.Check(moduleId))
            break;
          if (std::find(created.begin(), created.end(), requireId) == created.end())
          {
            this_postponed = true;
            break;
          }
        }
        if (this_postponed)
        {
          postponed = true;
          continue;
        }
        auto &&module = moduleTest.create();
        modules.emplace(Module::StageIndex(moduleTest.stage, moduleId), std::move(module));
        created.emplace_back(moduleId);
      }
      if (!postponed)
        break;
    }
    PLOGD << "Engine modules initialized";
  }

  Engine::~Engine()
  {
    CVars::Get()->ClearStorage();
    ModuleShutdown();
    app = nullptr;
    Module::Registry().clear();
    server->shutdown(true);
    server = nullptr;
    PLOGD << "engine terminated";
  }

  int32_t Engine::Run()
  {
    while (running)
    {
      Window::Get()->ActivateContext();

      if (app)
      {
        if (!app->started)
        {
          app->Start();
          app->started = true;
          PLOGD << "App started";
        }
        app->BeforeUpdate();
        PreUpdate();
        app->Update();
      }

      if (!events->started) {
        events->RunTasks();
        events->started = true;
      }

      // Always-Update.
      UpdateStage(Module::Stage::Always);

      // Pre-Update.
      UpdateStage(Module::Stage::Pre);

      // Update.
      UpdateStage(Module::Stage::Normal);

      // Post-Update.
      UpdateStage(Module::Stage::Post);

      // Updates the engines delta.
      deltaUpdate.Update();

      // Render
      if (elapsedRender.GetElapsed() != 0)
      {
        UpdateStage(Module::Stage::Render);
        fps.Update(Time::Now());
        deltaRender.Update();
      }

      app->AfterUpdate();

      PostUpdate();

      Window::Get()->SwapBuffers();
    }

    PLOGI << "engine stopped OK";
    return EXIT_SUCCESS;
  }

  void Engine::UpdateStage(Module::Stage stage)
  {
    for (auto &[stageIndex, module] : modules)
    {
      if (stageIndex.first == stage)
        module->Update();
    }
  }

  void Engine::PreUpdate()
  {
    for (auto &[stageIndex, module] : modules)
    {
      module->BeforeUpdate();
    }
  }

  void Engine::PostUpdate()
  {
    for (auto &[stageIndex, module] : modules)
    {
      module->AfterUpdate();
    }
  }

  void Engine::ModuleShutdown()
  {
    for (auto &[stageIndex, module] : modules)
    {
      module->Shutdown();
    }
  }
} // namespace mtEngine
