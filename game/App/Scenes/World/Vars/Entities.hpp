#pragma once

#include <string>
#include <vector>

#include <Engine/CVars.hpp>
#include <Scenes/Scenes.hpp>

#include "Config.hpp"
#include "Models/Model.hpp"
#include "Resources/ResourcesManager.hpp"
#include "Scenes/Components/Transform.hpp"
#include "Scenes/EntityManager.hpp"
#include "third_party/plog/Log.h"
namespace Game
{
  using namespace mtEngine;
  class Entities
  {
  public:
    Entities()
    {
      using CVarParam = std::vector<std::string>;
      using Input = std::vector<std::string>;
      CVars::Get()->Add("scenes", "entity_list", {""}, "List all entities", "scenes entity_list",
          [this](CVarParam &args, Input &input, bool &isValid)
          {
            isValid = true;
            const auto ent = mtEngine::Scenes::Get()->GetStructure()->QueryAll();
            PLOGI;
            PLOGI << "== Entities in memory: ==";
            for (const auto &e : ent)
            {
              PLOGI << e->GetName();
            }
            PLOGI;
          });

      CVars::Get()->Add("scenes", "entity_add", {""}, "Create Entity and add to scene",
          "scenes add_entity </Game/models/filename.gltf>",
          [this](CVarParam &args, Input &input, bool &isValid)
          {
            if (input.empty())
            {
              isValid = false;
              return;
            }
            const std::string path = input.at(0);
            if(input.at(1).empty()) {
              PLOGD << "name required";
              isValid = false;
              return;
            }
            const std::string name = input.at(1);
            const std::string p(RESOURCES);
            EntityManager::Add(p + path, name);
            isValid = true;
          });

      CVars::Get()->Add("scenes", "entity_rm", {""}, "Remove entity", "scenes rm_entity <name>",
          [this](CVarParam &args, Input &input, bool &isValid)
          {
            if (input.empty())
            {
              isValid = false;
              return;
            }
            const auto name = input.at(0);
            EntityManager::Remove(name);
            isValid = true;
          });
    };
    ~Entities()
    {
      CVars::Get()->RemoveName("scenes", "entity_add");
      CVars::Get()->RemoveName("scenes", "entity_rm");
      CVars::Get()->RemoveName("scenes", "entity_list");
    };
  };
} // namespace Game
