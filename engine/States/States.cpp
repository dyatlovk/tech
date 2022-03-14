#include "States.hpp"

namespace mtEngine {
  States::States()
  {
    std::cout << "states constructor" << std::endl;
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
