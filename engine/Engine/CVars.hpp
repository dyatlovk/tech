#pragma once

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
    constexpr static std::string_view VAR_FLAG = "var";

    using ClientArgs = std::vector<std::string>;
    using InputArgs = std::vector<std::string>;

    struct Commands
    {
      std::string group = "" ;
      std::string name  = "" ;
      ClientArgs args        ;
    } t_commands;

    struct Value
    {
      std::string group       = ""                                     ;
      std::string name        = ""                                     ;
      std::string description = ""                                     ;
      std::string help        = ""                                     ;
      ClientArgs args                                                  ;
      bool readOnly           = false                                  ;
      std::string type        = ""                                     ;
      std::function<void(ClientArgs &args, InputArgs &input, bool &isValid)> callback ;
    } t_values;

    // {group, {values...}}
    using VarsCommands = std::vector<Value>;
    using VarsMap = std::map<std::string, VarsCommands>;

  public:
    CVars();

    ~CVars();

    static std::unique_ptr<CVars> Init() { return std::make_unique<CVars>(); }

    static CVars *Get() { return Instance; }

    void Add(const std::string &group,
        const std::string &name,
        const std::vector<std::string> &args,
        const std::string &description,
        const std::string &help,
        std::function<void(ClientArgs &args, InputArgs &input, bool &isValid)> callback,
        const std::string &type = "var",
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
    VarsMap::iterator find(const std::string &group, const std::string &name);
    VarsMap::iterator findGroup(const std::string &group);
    bool containCommand(const std::string &name, VarsMap::iterator &group);
    Value &getCommand(const std::string &name, const VarsMap::iterator &group);
    Commands *parse(const std::string &args);

    VarsMap::iterator addGroup(const std::string &name);

    VarsMap m_cvars;

    Delegate<void(std::string name, std::vector<std::string> values)> onUpdate;
  };
} // namespace mtEngine
