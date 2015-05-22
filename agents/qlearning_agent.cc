#include "agents/qlearning_agent.h"

#include <vector>

#include "util/gtl/map_util.h"

namespace ttt {

bool QLearningAgent::Update(float reward, bool last_state) {
  const State *state = state_handler_.Get(state_id_);
  vector<float> &q = LookupOrInsert(&state_action_, state->ToString(),
                                    vector<float>(actions_.size(), 0.0));
  if (last_state) {
    q[action_] += config_.alpha() * (reward - q[action_]);
  } else {
    // Take the best possible next action.
    float next_q = 0.0;
    const State *next_state = state_handler_.Get(next_state_id_);
    const string next_state_key = next_state->ToString();
    if (!ContainsKey(state_action_, next_state_key)) {
      LookupOrInsert(&state_action_, next_state_key,
                     vector<float>(actions_.size(), 0.0));
      next_action_ = actions_.Random(next_state);
    } else {
      const vector<float> &action_scores =
          FindOrDie(state_action_, next_state_key);
      const vector<int> actions = Sort(action_scores);
      for (int i = 0; i < actions.size(); ++i) {
        if (next_state->Valid(actions[i])) {
          next_q = action_scores[actions[i]];
          next_action_ = actions[i];
          break;
        }
      }
    }
    q[action_] += config_.alpha() * (reward + config_.gamma() *
                                     next_q - q[action_]);
  }
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

void QLearningAgent::SetNextAction(const State *state) {
  next_state_id_ = state->id();
  // We intentionally don't get a next action since this is an off-policy
  // agent and the action is selected independently.
}

}  // namespace ttt
