#include "agents/human_agent.h"

#include <iostream>
#include <vector>

namespace ttt {

bool HumanAgent::Update(float reward, bool last_state) {
  // Intentionally left blank.
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

void HumanAgent::SetAction(const State *state) {
  state_id_ = state->id();
  std::cout << state->DebugString() << "\nAction? [0-8] ";
  std::cin >> action_;
  while (!state->Valid(action_)) {
    std::cout << "\nSpecify a valid action [0-8]: ";
    std::cin >> action_;
  }
}

void HumanAgent::SetNextAction(const State *state) {
  next_state_id_ = state->id();
  std::cout << state->DebugString() << "\nAction [0-8]: ";
  std::cin >> next_action_;
  while (!state->Valid(next_action_)) {
    std::cout << "\nSpecify a valid action [0-8]: ";
    std::cin >> next_action_;
  }
}

}  // namespace ttt
