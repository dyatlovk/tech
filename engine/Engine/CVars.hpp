#pragma once

#include <functional>
#include <map>
#include <any>
#include <string>
#include <cxxabi.h>
#include "Utils/NonCopyable.hpp"
#include "Engine/Log.hpp"

namespace mtEngine
{
  class CVars : public NonCopyable
  {
    constexpr static std::string_view COMMAND_FLAG = "command";

    struct Value {
      std::any val;
      std::any def_value;
      std::string help;
      bool readOnly = false;
      std::string type;
      std::function<void()> command;
    } t_values;
    public:
      CVars();

      ~CVars();

      static std::unique_ptr<CVars> Init() { return std::make_unique<CVars>(); }

      static CVars* Get() { return Instance; }

      template< typename T >
        void Add(const std::string& name, const T &value, const T &defaultValue, const std::string& help, const bool readOnly = false)
        {
          std::string type = Demangle(typeid(T).name());
          if(type.find("char") != std::string::npos) {
            type = "char";
          }
          t_values.val = value;
          t_values.help = help;
          t_values.def_value = value;
          t_values.readOnly = readOnly;
          t_values.type = type;
          m_cvars.emplace(std::make_pair(name, t_values));
          PLOGD << "cvar add: {" << name << ", " << value << ", " << defaultValue << ", " << t_values.type << "}";
        }
      
      void Add(const std::string& name, std::function<void()> callback, const std::string& help);

      void Exec(const std::string &name);

      template< typename T >
        void Update(const std::string& name, T value)
        {
          if(find(name)) {
            if(!m_find->second.readOnly) {
              m_find->second.val = value;
              return;
            }
            PLOGD << name << " readonly flag";
          }
        }
      template< typename T >
        T GetVar(const std::string &name)
        {
          try {
            find(name);
          } catch (const std::exception&) {
            PLOGD << "var not found";
          }
          return std::any_cast<T>(m_find->second.val);
        }

      std::string GetHelp(const std::string &name);

      void Reset(const std::string &name);

      void clearStorage()
      {
        m_cvars.clear();
      }

      std::map<std::string, Value> getList()
      {
        return m_cvars;
      }

      std::string getType(const std::string &name);

    private:
      static CVars *Instance;
      std::string Demangle(const char* mangled);
      bool find(const std::string &name);
      void ExecCommand(const std::string &name, const Value &found);
      void ExecVar(const std::string &name, const Value &found);
      
      std::map<std::string, Value> m_cvars;
      std::map<std::string, Value>::iterator m_find;
  };
}
