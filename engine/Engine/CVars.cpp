#include "CVars.hpp"

namespace mtEngine {
  CVars *CVars::Instance = nullptr;

  CVars::CVars()
  {
    Instance = this;
  };

  CVars::~CVars() = default;

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
}
