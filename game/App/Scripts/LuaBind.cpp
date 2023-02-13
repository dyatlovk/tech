#include "LuaBind.hpp"

#include <functional>

#include "third_party/plog/Log.h"

namespace Game
{
  Lua *Lua::Instance = nullptr;
  Lua::Lua()
      : m_state(new sol::state())
      , m_scriptsPath("")
  {
    Instance = this;
  }
  Lua::~Lua()
  {
    m_state = nullptr;
    delete m_state;
  }

  auto Lua::GetState() -> sol::state *
  {
    return m_state;
  }

  auto Lua::Init() -> std::unique_ptr<Lua>
  {
    auto s = std::make_unique<Lua>();

    return s;
  }

  auto Lua::SetPackageRoot(const std::string &path) -> void
  {
    m_scriptsPath = path;
    const std::string package_path = m_state->get<sol::table>("package").get<std::string>("path");
    auto package = m_state->get<sol::table>("package");
    auto newPath = package_path + (!package_path.empty() ? ";" : "") + path + "?.lua;" + package_path;
    package.set("path", newPath);
  }

  auto Lua::Execute(const std::string &file) -> void
  {
    auto result = m_state->load_file(m_scriptsPath + file);

    if (!result.valid())
    {
      PLOGI << "script << " << file << " not valid or not found";
      return;
    }

    result();
  }
} // namespace Game
