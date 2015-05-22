#include "agents/sarsa_agent.h"

#include <vector>

namespace ttt {

bool SarsaAgent::Update(float reward, bool last_state) {
  const State *state = state_handler_.Get(state_id_);
  if (state_action_.find(state->ToString()) == state_action_.end()) {
    state_action_[state->ToString()] = std::vector<float>(actions_.size(), 0.0);
  }
  std::vector<float> &q = state_action_[state->ToString()];
  if (last_state) {
    q[action_] += config_.alpha() * (reward - q[action_]);
  } else {
    const State *next_state = state_handler_.Get(next_state_id_);
    if (state_action_.find(next_state->ToString()) == state_action_.end()) {
      state_action_[next_state->ToString()] =
          std::vector<float>(actions_.size(), 0.0);
    }
    const std::vector<float> &next_q = state_action_[next_state->ToString()];
    q[action_] += config_.alpha() * (reward + config_.gamma() *
                                     next_q[next_action_] - q[action_]);
  }
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

}  // namespace ttt
