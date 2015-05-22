#include "agents/random_agent.h"

#include <vector>

namespace ttt {

bool RandomAgent::Update(float reward, bool last_state) {
  // Intentionally left blank.
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

void RandomAgent::SetAction(const State *state) {
  state_id_ = state->id();
  action_ = actions_.Random(state);
}

void RandomAgent::SetNextAction(const State *state) {
  next_state_id_ = state->id();
  next_action_ = actions_.Random(state);
}

REGISTER_AGENT(RandomAgent);

}  // namespace ttt
