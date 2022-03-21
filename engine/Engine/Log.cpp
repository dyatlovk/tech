#include "Log.hpp"

namespace mtEngine
{
  Log *Log::Instance = nullptr;

  Log::Log()
  {
    Instance = this;
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    static MemoryAppender<plog::MessageOnlyFormatter> mem;
    memAppender = mem;
    plog::init(plog::verbose, &consoleAppender).addAppender(&memAppender);
    PLOGD << "log start";
  }

  Log::~Log() = default;
} // namespace mtEngine
