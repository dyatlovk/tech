#include "CVars.hpp"
#include <any>
#include <cstdarg>
#include <sstream>
#include <string>
#include "Utils/String.hpp"

namespace mtEngine {
  CVars *CVars::Instance = nullptr;

  CVars::CVars()
  {
    Instance = this;
    PLOGD << "cvars start";
  };

  CVars::~CVars() = default;

  void CVars::Add(const std::string& name, std::function<void()> callback, const std::string& help)
  {
    t_values.val = "";
    t_values.help = help;
    t_values.readOnly = true;
    t_values.type = COMMAND_FLAG;
    t_values.def_value = "";
    t_values.command = callback;
    m_cvars.emplace(std::make_pair(name, t_values));
    PLOGD << "cvar add: {" << name << ", " << help << ", command}";
  }

  void CVars::Exec(const std::string &args)
  {
    auto tokens = Split(args, " ");
    if(tokens.size() == 0) return;
    auto name = tokens.at(0);
    if(name.compare("") == 0) return;
    if(!find(name)) {
      PLOGD << "vars: " << name << " not found";
      return;
    }
    auto found = m_find->second;
    // found command
    if(found.type == COMMAND_FLAG) {
      ExecCommand(name, found);
      return;
    }
    // found var
    if(found.type != COMMAND_FLAG) {
      tokens.erase(tokens.begin()); // keep args, remove name
      ExecVar(name, found, tokens);
      return;
    }
    PLOGD << "var: " << name << " unknown type: ["  << t_values.type << "]";
  }

  std::string CVars::GetHelp(const std::string &name)
  {
    if(find(name)) {
      return m_find->second.help;
    }

    return "";
  }

  void CVars::Reset(const std::string &name)
  {
    if(find(name)) {
      m_find->second.val = m_find->second.def_value;
    }
  }

  std::string CVars::getType(const std::string &name)
  {
    if(find(name))
    {
      return m_find->second.type;
    }

    return "undefined";
  }

  bool CVars::find(const std::string &name)
  {
    auto search = m_cvars.find(name);
    if(search != m_cvars.end()) {
      m_find = search;
      return true;
    }

    return false;
  }

  std::string CVars::Demangle(const char *mangled)
  {
    int status; 
    std::unique_ptr<char[], void (*)(void*)> result( abi::__cxa_demangle(mangled, 0, 0, &status), std::free); 
    return result.get() ? std::string(result.get()) : "error occurred";
  }

  void CVars::ExecCommand(const std::string &name, const Value &found)
  {
    found.command();
  }

  void CVars::ExecVar(const std::string &name, Value &found, std::vector<std::string> newVal)
  {
    const char *readOnlyMgs = " [RW]";
    if(found.readOnly) {
      readOnlyMgs = " [R]"; 
    }
    if(t_values.type.find("char") != std::string::npos) {
      std::ostringstream ss;
      if(newVal.size() > 0 && !found.readOnly) {
        for(auto it = newVal.begin(); it != newVal.end(); ++it) {
          if(it == newVal.begin()) {
            ss << it->data() << " ";
          } else if(it == newVal.end()) {
            ss << " " << it->data();
          } else {
            ss << it->data();
          }
        } 
        m_find->second.val = ss.str();
      }
      PLOGD << name << ": \"" << std::any_cast<std::string>(m_find->second.val) << "\"" << readOnlyMgs;
      return;
    }
    if(t_values.type == "int") {
      PLOGD << name << ": \"" << std::any_cast<int>(m_find->second.val) << "\"" << readOnlyMgs;
      return;
    }
    if(t_values.type == "float") {
      PLOGD << name << ": \"" << std::any_cast<float>(m_find->second.val) << "\"" << readOnlyMgs;
      return;
    }
    if(t_values.type == "double") {
      PLOGD << name << ": \"" << std::any_cast<double>(m_find->second.val) << "\"" << readOnlyMgs;
      return;
    }
  }
}
