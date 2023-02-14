#include "LuaBind.hpp"

#include <memory>

#include "third_party/plog/Log.h"

namespace mtEngine
{
  LuaBind *LuaBind::Instance = nullptr;
  LuaBind::LuaBind()
      : m_state(new sol::state())
      , m_scriptsPath("")
  {
    Instance = this;
  }
  LuaBind::~LuaBind()
  {
    m_state = nullptr;
    delete m_state;
  }

  auto LuaBind::GetState() -> sol::state *
  {
    return m_state;
  }

  auto LuaBind::Init() -> std::unique_ptr<LuaBind>
  {
    auto s = std::make_unique<LuaBind>();

    return s;
  }

  auto LuaBind::SetPackageRoot(const std::string &path) -> void
  {
    m_scriptsPath = path;
    const std::string package_path = m_state->get<sol::table>("package").get<std::string>("path");
    auto package = m_state->get<sol::table>("package");
    auto newPath = package_path + (!package_path.empty() ? ";" : "") + path + "?.lua;" + package_path;
    package.set("path", newPath);
  }

  auto LuaBind::Execute(const std::string &file) -> void
  {
    auto result = m_state->load_file(m_scriptsPath + file);

    if (!result.valid())
    {
      PLOGI << "script << " << file << " not valid or not found";
      return;
    }

    result();
  }
} // namespace mtEngine
