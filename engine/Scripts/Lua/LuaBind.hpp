#pragma once

#include "Utils/NonCopyable.hpp"
#define SOL_ALL_SAFETIES_ON 1

#include <third_party/sol/sol.hpp>

namespace mtEngine
{
  class LuaBind : public NonCopyable
  {
  public:
    LuaBind();
    ~LuaBind() override;

    // ---------------------------------------------------------------------------
    auto static Get() -> LuaBind * { return Instance; };

    auto GetState() -> sol::state *;

    // ---------------------------------------------------------------------------
    auto static Init() -> std::unique_ptr<LuaBind>;

    // ---------------------------------------------------------------------------
    // Where scripts stored
    auto SetPackageRoot(const std::string &path) -> void;

    // ---------------------------------------------------------------------------
    // File path relative to scripts path with extension
    auto Execute(const std::string &file) -> void;

    // ---------------------------------------------------------------------------
    // Register user type on global space and bind to lua
    template<typename Class>
    auto Register(const std::string &name) -> sol::usertype<Class>
    {
      auto type = m_state->new_usertype<Class>(name);
      auto instance = std::make_shared<Class>();
      m_state->set(name, std::move(instance));

      return type;
    }

    // ---------------------------------------------------------------------------
    // Register user type in namespace and bind to lua
    template<typename Class>
    auto Register(const std::string &ns, const std::string &name) -> sol::usertype<Class>
    {
      auto namesp = m_state->set(ns).get_or(ns, m_state->create_table(ns));
      auto type = namesp.new_usertype<Class>(name);
      auto instance = std::make_shared<Class>();
      namesp.set(name, std::move(instance));

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
    static LuaBind *Instance;
  };
} // namespace mtEngine
