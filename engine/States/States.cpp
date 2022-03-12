#include "States.hpp"

namespace mtEngine {
  States::States()
  {
    Set(State::Default);
  };

  void States::Update()
  {

  }

  void States::Set(State state)
  {
    current = state;
    onState(current);
  }
}
