#pragma once

#include "third_party/plog/Log.h"
#include "third_party/plog/Init.h"
#include "third_party/plog/Appenders/ColorConsoleAppender.h"
#include "third_party/plog/Formatters/TxtFormatter.h"
#include "third_party/plog/Formatters/MessageOnlyFormatter.h"
#include "third_party/plog/Formatters/FuncMessageFormatter.h"
#include <list>

namespace mtEngine {
  using namespace plog;
  template<class Formatter> // Typically a formatter is passed as a template parameter.
  class MemoryAppender : public IAppender // All appenders MUST inherit IAppender interface.
  {
    public:
      virtual void write(const Record& record) // This is a method from IAppender that MUST be implemented.
      {
        util::nstring str = Formatter::format(record); // Use the formatter to get a string from a record.

        m_messageList.push_back(str); // Store a log message in a list.
      }

      std::list<util::nstring> &getMessageList()
      {
        return m_messageList;
      }

    private:
      std::list<util::nstring> m_messageList;
  };

  class Log {
    private:
      MemoryAppender<plog::MessageOnlyFormatter> memAppender;
    public:
      Log() {
        static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
        static MemoryAppender<plog::MessageOnlyFormatter> mem;
        memAppender = mem;
        plog::init(plog::verbose, &consoleAppender).addAppender(&memAppender);
        PLOGD << "log start";
      };

      ~Log() {};

       std::list<util::nstring> GetMomory() { return memAppender.getMessageList(); }
  };
}
