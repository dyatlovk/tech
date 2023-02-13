#pragma once

#include <any>
#include <memory>

#include "Utils/NonCopyable.hpp"
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

namespace Game
{
  using namespace mtEngine;
  class Lua : public NonCopyable
  {
  public:
    Lua();
    ~Lua() override;

    // ---------------------------------------------------------------------------
    auto static Get() -> Lua * { return Instance; };

    auto GetState() -> sol::state *;

    // ---------------------------------------------------------------------------
    auto static Init() -> std::unique_ptr<Lua>;

    // ---------------------------------------------------------------------------
    // Where scripts stored
    auto SetPackageRoot(const std::string &path) -> void;

    // ---------------------------------------------------------------------------
    // File path relative to scripts path with extension
    auto Execute(const std::string &file) -> void;

    // ---------------------------------------------------------------------------
    // Register user type and bind to lua
    template<typename Class>
    auto Register(const std::string &name) -> sol::usertype<Class>
    {
      auto type = m_state->new_usertype<Class>(name);
      // for (const auto &m : methods)
      // {
      //   type[m.first] = m.second;
      // }
      auto instance = std::make_shared<Class>();
      m_state->set(name, std::move(instance));

      return type;
    }

    // ---------------------------------------------------------------------------
    // Call lua function
    auto RunFunction(const std::string &name) -> void
    {
      sol::protected_function func = m_state->get<sol::function>(name);
      func();
    }

  private:
    sol::state *m_state;

    // where is lua scripts
    std::string m_scriptsPath;

    // where is game root
    std::string m_root;
    static Lua *Instance;
  };
} // namespace Game
