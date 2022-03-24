#include "CVars.hpp"

#include <algorithm>
#include <iterator>
#include <stdexcept>

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

  void CVars::Add(const std::string &group, const std::string &name,
      const std::vector<std::string> &args, const std::string &description,
      const std::string &help, std::function<void(ClientArgs &args)> callback,
      bool readOnly)
  {
    auto foundGroup = findGroup(group);
    auto isCommandExist = containCommand(name, foundGroup);

    if (foundGroup == m_cvars.end())
    {
      foundGroup = addGroup(group);
    }

    t_values.args = args;
    t_values.name = name;
    t_values.group = group;
    t_values.description = description;
    t_values.help = help;
    t_values.callback = callback;
    t_values.readOnly = readOnly;

    foundGroup->second.push_back(t_values);

    PLOGD << "cvars add: " << name << ": {" << description << ", " << help << "}";
    return;
  }

  /**
   * Command template <group var args...>
   */
  void CVars::Exec(const std::string &command)
  {
    auto commands = parse(command);
    if (!commands)
    {
      PLOGD << "cvar require group and name";
      return;
    };

    // group found
    auto foundGroup = findGroup(commands->group);
    if (foundGroup == m_cvars.end())
    {
      PLOGE << "cvar: " << commands->group << " not found";
      return;
    }

    VarsCommands groupCommands = foundGroup->second;

    // no command name
    // print all commands in group
    if (commands->name.compare("") == 0)
    {
      PLOGD << commands->group << " " << commands->name;
      for (const auto &f : groupCommands)
      {
        PLOGD << "\t - " << f.name;
      }
      return;
    }

    // check args
    Value foundCommand;
    try
    {
      foundCommand = getCommand(commands->name, foundGroup);
    }
    catch (const std::exception& e)
    {
      PLOGE << e.what();
      return;
    }

    PLOGD << "found command: " << foundCommand.name << " args: " << String::dump(foundCommand.args);
  }

  void CVars::Update(const std::string &group, const std::string &name)
  {
    for (auto it = m_cvars.find(group); it != m_cvars.end(); it++)
    {
    }
  }

  CVars::VarsMap::iterator CVars::find(
      const std::string &group, const std::string &name)
  {
    auto foundGroup = findGroup(group);

    if (foundGroup == m_cvars.end())
    {
      return m_cvars.end();
    }

    return m_cvars.begin();
  }

  CVars::VarsMap::iterator CVars::findGroup(const std::string &group)
  {
    auto found = m_cvars.find(group);
    if (found != m_cvars.end())
      return m_cvars.begin();

    return m_cvars.end();
  }

  bool CVars::containCommand(const std::string &name, VarsMap::iterator &group)
  {
    auto values = group->second;

    for (const auto v : values)
    {
      if (v.name == name)
      {
        return true;
      }
    }
    return false;
  }

  CVars::Value CVars::getCommand(const std::string &name, const VarsMap::iterator &group) const
  {
    auto values = group->second;
    for (auto v : values)
    {
      if (v.name == name)
      {
        return v;
      }
    }

    std::string exceptionMsg = "command" + name + " not found";
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
    auto tokens = String::Split(args);
    if (tokens.size() == 0)
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
