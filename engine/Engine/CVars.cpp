#include "CVars.hpp"
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
    t_values.args = args;
    t_values.name = name;
    t_values.group = group;
    t_values.description = description;
    t_values.help = help;
    t_values.callback = callback;
    t_values.readOnly = readOnly;

    m_cvars.emplace(group, t_values);
    PLOGD << "cvars add: " << name << ": {" << description << ", " << help << "}";
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

    find(commands->group, commands->name);
    if (m_found.size() == 0)
    {
      PLOGD << "cvar: " << commands->name << " not found";
      return;
    }

    if (m_found.size() > 1)
    {
      PLOGD << commands->group << " " << commands->name;
      for (const auto &f : m_found)
      {
        PLOGD << "\t - " << f.name;
      }
      return;
    }

    auto com = m_found.at(0);
    com.callback(commands->args);
    if(commands->args.size() > 0) {
      com.args = commands->args;
    }
    PLOGD << com.group << "::" << com.name << " " << String::dump(com.args);
  }

  void CVars::Update(const std::string &group, const std::string &name)
  {
      for (auto it = m_cvars.find(group); it != m_cvars.end(); it++) {

      }
  }

  void CVars::find(const std::string &group, const std::string &name)
  {
    m_found.clear();
    if (name == "")
    {
      for (auto it = m_cvars.find(group); it != m_cvars.end(); it++)
      {
        m_found.push_back(it->second);
      }
      return;
    }

    for (auto it = m_cvars.find(group); it != m_cvars.end(); it++)
    {
      if (name == it->second.name)
      {
        m_found.push_back(it->second);
        return;
      }
    }
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
