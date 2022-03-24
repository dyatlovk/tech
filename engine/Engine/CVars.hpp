#pragma once

#include <any>
#include <cxxabi.h>
#include <functional>

#include "Engine/Log.hpp"
#include "Utils/Delegate.hpp"
#include "Utils/NonCopyable.hpp"

namespace mtEngine
{
  class CVars : public NonCopyable
  {
    constexpr static std::string_view COMMAND_FLAG = "command";

    using ClientArgs = std::vector<std::string>;

    struct Commands
    {
      std::string group;
      std::string name;
      std::vector<std::string> args;
    } t_commands;

    struct Value
    {
      std::string group;
      std::string name;
      std::string val;
      std::string description;
      std::string def_val = val;
      std::string help;
      std::vector<std::string> args;
      bool readOnly = false;
      std::string type;
      std::function<void(ClientArgs &args)> callback;
    } t_values;

    using VarsMap = std::multimap<std::string, Value>;
    using FoundContainer = std::vector<Value>;

  public:
    CVars();

    ~CVars();

    static std::unique_ptr<CVars> Init() { return std::make_unique<CVars>(); }

    static CVars *Get() { return Instance; }

    void Add(const std::string &group, const std::string &name,
        const std::vector<std::string> &args, const std::string &description,
        const std::string &help, std::function<void(ClientArgs &args)> callback,
        bool readOnly = false);
    void Exec(const std::string &args);

    void Update(const std::string &group, const std::string &name);

    void ClearStorage() { m_cvars.clear(); }

    VarsMap getList() { return m_cvars; }

    std::string getType(const std::string &name);

    Delegate<void(std::string name, std::vector<std::string> values)> &
    OnUpdate()
    {
      return onUpdate;
    }

  private:
    static CVars *Instance;
    std::string Demangle(const char *mangled);
    void find(const std::string &group, const std::string &name);
    Commands *parse(const std::string &args);

    VarsMap m_cvars;
    FoundContainer m_found;

    Delegate<void(std::string name, std::vector<std::string> values)> onUpdate;
  };
} // namespace mtEngine
