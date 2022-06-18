#include "CVars.hpp"

#include <iterator>
#include <utility>

#include "Utils/String.hpp"

namespace mtEngine
{
  CVars *CVars::Instance = nullptr;

  CVars::CVars()
  {
    Instance = this;
    PLOGD << "cvars start";
  };

  CVars::~CVars() = default;

  void CVars::Add(const std::string &group,
      const std::string &name,
      const std::vector<std::string> &args,
      const std::string &description,
      const std::string &help,
      std::function<void(ClientArgs &args, InputArgs &input, bool &isValid)> callback,
      const std::string &type, bool readOnly)
  {
    auto foundGroup = findGroup(group);

    if (foundGroup == m_cvars.end())
    {
      foundGroup = addGroup(group);
    }

    t_values.args        = args;
    t_values.name        = name;
    t_values.group       = group;
    t_values.description = description;
    t_values.help        = help;
    t_values.callback    = std::move(callback);
    t_values.readOnly    = readOnly;
    t_values.type        = type;

    foundGroup->second.push_back(t_values);

    PLOGD << "cvars add: " << group << "::" << name << "{" << description << "}";
  }

  /**
   * Command template <group var args...>
   */
  void CVars::Exec(const std::string &command)
  {
    auto commands = parse(command);
    if (!commands)
    {
      return;
    };

    // group found
    auto foundGroup = findGroup(commands->group);
    if (foundGroup == m_cvars.end())
    {
      PLOGE << "cvar: " << commands->group << " not found";
      return;
    }

    VarsCommands &groupCommands = foundGroup->second;

    // no command name
    // print all commands in group
    if (commands->name.empty())
    {
      std::string permission = "[RW]";
      PLOG_NONE;
      PLOGD << "[" << commands->group << "] " << commands->name;
      PLOGD << "-----------------------------------------------";
      for (const auto &f : groupCommands)
      {
        std::string values;
        if(f.readOnly) permission = "[R]";
        if(f.type == VAR_FLAG && f.args.size() != 0) values = String::dump(f.args);
        if(values.empty()) {
          PLOGD << f.name;
        } else {
          PLOGD << f.name << ": \"" << values << "\" " << permission;
        }
      }
      PLOGD << "-----------------------------------------------";
      return;
    }

    Value &foundCommand = t_values;
    try {
      foundCommand = getCommand(commands->name, foundGroup);
    } catch (std::invalid_argument &e) {
      PLOGE << "cvar: " << commands->group << "::" << commands->name << " not found";
      return;
    }

    // exec command firstly
    bool isValid = false;
    if(foundCommand.type == COMMAND_FLAG) {
      foundCommand.callback(foundCommand.args, commands->args, isValid);
      return;
    }
    
    // check args
    if(foundCommand.args.empty()) {
      PLOGD << foundCommand.group << "::" << foundCommand.name << " \"" << String::dump(foundCommand.args) << "\"";
      return;
    }
    
    ClientArgs clientArgs;
    if(commands->args.empty()) {
      PLOGD << foundCommand.group << "::" << foundCommand.name << " \"" << String::dump(foundCommand.args) << "\"";
      return;
    }

    foundCommand.callback(foundCommand.args, commands->args, isValid);
    if(foundCommand.readOnly) {
      PLOGD << foundCommand.group << "::" << foundCommand.name << " \"" << String::dump(foundCommand.args) << "\"";
      return;
    }
    PLOGD << "callback: " << String::dump(commands->args);
    foundCommand.args = commands->args;

    PLOGD << foundCommand.group << "::" << foundCommand.name << " \"" << String::dump(foundCommand.args) << "\"";
  }

  void CVars::Update(const std::string &group, const std::string &name)
  {
    for (auto it = m_cvars.find(group); it != m_cvars.end(); it++)
    {
    }
  }

  void CVars::RemoveGroup(const std::string &name)
  {
    auto found = findGroup(name);
    m_cvars.erase(found);
  }

  void CVars::ClearGroup(const std::string &name)
  {
    auto found = findGroup(name);
    found->second.clear();
  }

  void CVars::RemoveName(const std::string &group, const std::string &name)
  {
    auto found = findGroup(group);
    try {
      auto cmdIt = find(group, name);
      found->second.erase(cmdIt);
    } catch (std::invalid_argument &e) {
      PLOGD << "cvar: " << group << "::" << name << " not found";
    }
  }

  CVars::VarsCommands::iterator CVars::find(const std::string &group, const std::string &name)
  {
    auto foundGroup = findGroup(group);
    auto values = foundGroup->second;
    for (auto it = values.begin(); it != values.end(); it++)
    {
      if(it->name == name) {
        return it;
      }
    }

    std::string exceptionMsg = name + " not found";
    throw std::invalid_argument(exceptionMsg);
  }

  CVars::VarsMap::iterator CVars::findGroup(const std::string &group)
  {
    auto found = m_cvars.find(group);
    if (found != m_cvars.end())
      return found;

    return m_cvars.end();
  }

  bool CVars::containCommand(const std::string &name, VarsMap::iterator &group)
  {
    auto values = group->second;

    for (const auto& v : values)
    {
      if (v.name == name)
      {
        return true;
      }
    }
    return false;
  }

  CVars::Value &CVars::getCommand(const std::string &name, const VarsMap::iterator &group)
  {
    auto &values = group->second;
    for (auto &v : values)
    {
      if (v.name == name)
      {
        return v;
      }
    }

    std::string exceptionMsg = name + " not found";
    throw std::invalid_argument(exceptionMsg);
  }

  CVars::VarsMap::iterator CVars::addGroup(const std::string &name)
  {
    VarsCommands commands;
    auto it = m_cvars.emplace(name, commands);

    return it.first;
  }

  /**
   * index0: group
   * index1: name
   * other index: args
   */
  CVars::Commands *CVars::parse(const std::string &args)
  {
    if(args.empty()) return nullptr;
    auto tokens = String::Split(args);
    if (tokens.empty())
      return nullptr; // group required

    t_commands.group = "";
    t_commands.name = "";
    t_commands.args = {};

    // group only
    if (tokens.size() == 1)
    {
      t_commands.group = tokens.at(0);
      return &t_commands;
    }

    // group and name
    if (tokens.size() == 2)
    {
      t_commands.group = tokens.at(0);
      t_commands.name = tokens.at(1);
      tokens.erase(tokens.begin(), tokens.begin() + 2);
      return &t_commands;
    }

    // group, name, args
    t_commands.group = tokens.at(0);
    t_commands.name = tokens.at(1);
    tokens.erase(tokens.begin(), tokens.begin() + 2);
    t_commands.args = tokens;

    return &t_commands;
  }
} // namespace mtEngine
