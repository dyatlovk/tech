#include "AppCommands.hpp"

#include "Engine/Engine.hpp"
#include "Scenes/MainMenu/MainMenu.hpp"
#include "Scenes/World/World.hpp"
#include "Utils/String.hpp"

namespace Game
{
  // ---------------------------------------------------------------------------
  AppCommands::AppCommands()
      : threadPool(&Engine::Get()->GetApp()->GetThreadPool())
  {
  }

  // ---------------------------------------------------------------------------
  AppCommands::~AppCommands() {}

  // ---------------------------------------------------------------------------
  auto AppCommands::LoadScene() -> void
  {
    CVars::Get()->Add("scenes", "load", {""}, "Load scene", "scenes load main_menu",
        [this](CVarParam &args, Input &input, bool &isValid)
        {
          if (input.empty())
          {
            isValid = false;
            return;
          }

          if (input.at(0) == "main_menu")
          {
            isValid = true;
            mtEngine::Scenes::Get()->SetScene(std::make_unique<MainMenu>());
          }

          if (input.at(0) == "world")
          {
            isValid = true;
            mtEngine::Scenes::Get()->SetScene(std::make_unique<World>());
          }
        });
  }

  // ---------------------------------------------------------------------------
  auto AppCommands::ResourceLoad() -> void
  {
    CVars::Get()->Add("app", "resource_load", {"texture"}, "Load resource into stack",
        "resource_load <texture> <path/to/file> <name_in_stack>",
        [this](CVarParam &args, Input &input, bool &isValid)
        {
          if (input.empty())
          {
            PLOGD << "empty command args";
            isValid = false;
            return;
          }

          if (input.size() < 3)
          {
            isValid = false;
            PLOGD << "invalid command args";
            return;
          }

          auto type = input.at(0);
          auto path = input.at(1);
          auto name = input.at(2);
          if (type == "texture")
          {
            threadPool->Enqueue(
                [name, path]()
                {
                  sleep(10);
                  const std::string p(RESOURCES);
                  auto res = Texture::Create(name, p + path);
                  PLOGI << "resource: " << name << " loaded";
                });
            PLOGI << "resource: " << name << " try load async";
            isValid = true;
          }
        });
  }

  // ---------------------------------------------------------------------------
  auto AppCommands::ResourceInfo() -> void
  {
    CVars::Get()->Add(
        "app", "resource_info", {""}, "Get info about resources", "resource_info <type> <name>",
        [](CVarParam &args, Input &input, bool &isValid)
        {
          if (input.empty())
          {
            PLOGD << "empty command args";
            isValid = false;
            return;
          }
          if (input.size() < 2)
          {
            isValid = false;
            PLOGD << "invalid command args";
            return;
          }

          auto type = input.at(0);
          auto name = input.at(1);

          if (type == "texture")
          {
            auto res = ResourcesManager::Get()->find<Texture>(name);
            PLOGI << "resource " << res->GetTypeIndex().name() << " loaded";
            isValid = true;
          }
        },
        "var", true);
  }

  // ---------------------------------------------------------------------------
  auto AppCommands::ResourcesGet() -> void
  {
    CVars::Get()->Add("app", "resources", {"get"}, "Get info about all resources", "resources",
        [](CVarParam &args, Input &input, bool &isValid)
        {
          auto res = ResourcesManager::Get()->GetAll();
          PLOGI;
          PLOGI << "== Resources in memory: ==";
          std::vector<int> wordSizes;
          for (const auto &[key, resource] : res)
          {
            for (const auto &item : resource)
            {
              auto size = item.first.size();
              wordSizes.push_back((int)size);
            }
          }
          int maxSpaces = *max_element(wordSizes.begin(), wordSizes.end());
          std::string space = " ";
          for (auto i = 0; i < maxSpaces; ++i)
          {
            space += " ";
          }
          for (const auto &[key, resource] : res)
          {
            for (const auto &item : resource)
            {
              const auto itemSize = item.first.size();
              const auto itemSpaces = maxSpaces - itemSize;
              const auto _space = String::spaces(itemSpaces);
              PLOGI << item.first << _space << " | " << item.second->GetTypeIndex().name()
                    << " | uses: " << item.second.use_count();
            }
          }
          PLOGI;
          isValid = true;
          ServerSocket::Get()->emit("app resources command");
        });
  }

  // ---------------------------------------------------------------------------
  auto AppCommands::ResourceRemove() -> void
  {
    CVars::Get()->Add("app", "resource_rm", {""}, "Remove resource by name", "resource_rm <name>",
        [](CVarParam &args, Input &input, bool &isValid)
        {
          if (input.empty())
          {
            PLOGD << "empty command args";
            isValid = false;
            return;
          }
          isValid = true;
          const auto name = input.at(0);
          ResourcesManager::Get()->remove(name);
        });
  }

}; // namespace Game
