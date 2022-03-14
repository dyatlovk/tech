#pragma once

namespace mtEngine {
  class EnumStates
  {
    public:
      enum {
        Default = 0,
        Player  = 1,
        GUI     = 2,
      };
      EnumStates() {};
      ~EnumStates() {};
  };
}
