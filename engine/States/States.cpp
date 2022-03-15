#include "States.hpp"

namespace mtEngine {
  States::States()
  {
    PLOGD << "states construct";
    Set(EnumStates::Default);
  };

  void States::Update()
  {

  }

  void States::Set(int state)
  {
    current = state;
    onState(current);
  }
}
