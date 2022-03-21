#include "Engine.hpp"
#include <memory>

namespace mtEngine {
  Engine *Engine::Instance = nullptr;

  Engine::Engine(std::string argv0, ModuleFilter &&moduleFilter) :
    argv0(std::move(argv0)),
    version{VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH},
    fpsLimit(-1.0f),
    running(true) {
      Instance = this;
      log = Log::Init();
      cvars = CVars::Init();
      commands = Commands::Init();
      PLOGD << "start engine";

      // TODO: Optimize and clean up!
      std::vector<TypeId> created;
      for (;;) {
        bool postponed = false;
        for (const auto &[moduleId, moduleTest] : Module::Registry()) {
          if (std::find (created.begin(), created.end(), moduleId) != created.end())
            continue;
          if (!moduleFilter.Check (moduleId))
            continue;
          bool this_postponed = false;
          for (const auto &requireId : moduleTest.requires) {
            if (!moduleFilter.Check (moduleId))
              break;
            if (std::find(created.begin(), created.end(), requireId) == created.end()) {
              this_postponed = true;
              break;
            }
          }
          if (this_postponed) {
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
    }

  Engine::~Engine() {
    CVars::Get()->clearStorage();
    ModuleShutdown();
    app = nullptr;
    Module::Registry().clear();
  }

  int32_t Engine::Run() {
    while (running) {
      if (app) {
        if (!app->started) {
          app->Start();
          app->started = true;
        }
        app->BeforeUpdate();
        app->Update();
      }

      // Always-Update.
      UpdateStage(Module::Stage::Always);

      // Pre-Update.
      UpdateStage(Module::Stage::Pre);

      // Update.
      UpdateStage(Module::Stage::Normal);

      // Post-Update.
      UpdateStage(Module::Stage::Post);

      // Render
      UpdateStage(Module::Stage::Render);

      PostUpdate();

      app->AfterUpdate();
    }

    return EXIT_SUCCESS;
  }

  void Engine::UpdateStage(Module::Stage stage) {
    for (auto &[stageIndex, module] : modules) {
      if (stageIndex.first == stage)
        module->Update();
    }
  }

  void Engine::PostUpdate()
  {
    for (auto &[stageIndex, module] : modules) {
      module->AfterUpdate();
    }
  }
  
  void Engine::ModuleShutdown()
  {
    for (auto &[stageIndex, module] : modules) {
      module->Shutdown();
    }
  }
}
