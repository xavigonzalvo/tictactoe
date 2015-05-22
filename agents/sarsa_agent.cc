#include "experimental/users/xavigonzalvo/ttt/agents/sarsa_agent.h"

#include <vector>

#include "util/gtl/map_util.h"

namespace ttt {

bool SarsaAgent::Update(float reward, bool last_state) {
  const State *state = state_handler_.Get(state_id_);
  vector<float> &q = LookupOrInsert(&state_action_, state->ToString(),
                                    vector<float>(actions_.size(), 0.0));
  if (last_state) {
    q[action_] += config_.alpha() * (reward - q[action_]);
  } else {
    const State *next_state = state_handler_.Get(next_state_id_);
    const vector<float> &next_q =
        LookupOrInsert(&state_action_, next_state->ToString(),
                       vector<float>(actions_.size(), 0.0));
    q[action_] += config_.alpha() * (reward + config_.gamma() *
                                     next_q[next_action_] - q[action_]);
  }
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

REGISTER_AGENT(SarsaAgent);

}  // namespace ttt
