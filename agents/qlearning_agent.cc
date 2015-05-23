/*
The MIT License (MIT)

Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "agents/qlearning_agent.h"

#include <vector>

namespace ttt {

bool QLearningAgent::Update(float reward, bool last_state) {
  const State *state = state_handler_.Get(state_id_);
  if (state_action_.find(state->ToString()) == state_action_.end()) {
    state_action_[state->ToString()] = std::vector<float>(actions_.size(), 0.0);
  }
  std::vector<float> &q = state_action_[state->ToString()];
  if (last_state) {
    q[action_] += config_.alpha() * (reward - q[action_]);
  } else {
    // Take the best possible next action.
    float next_q = 0.0;
    const State *next_state = state_handler_.Get(next_state_id_);
    const std::string next_state_key = next_state->ToString();
    if (state_action_.find(next_state_key) == state_action_.end()) {
      state_action_[next_state_key] =
          std::vector<float>(actions_.size(), 0.0);
      next_action_ = actions_.Random(next_state);
    } else {
      const std::vector<float> &action_scores =
          state_action_[next_state_key];
      const std::vector<int> actions = Sort(action_scores);
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
