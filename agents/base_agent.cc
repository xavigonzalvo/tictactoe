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
#include "agents/base_agent.h"

#include <algorithm>
#include <fstream>

#include "agents/agent_model.pb.h"

namespace ttt {

BaseAgent::BaseAgent(const Config &config, const Actions &actions,
                     const StateHandler &state_handler)
    : config_(config), actions_(actions), state_handler_(state_handler),
      random_() {
}

int BaseAgent::SelectAction(const State *state) {
  // Explore random action.
  if (random_.RndFloat() < config_.epsilon()) {
    return actions_.Random(state);
  }
  // If not present, randomize action and insert empty scores.
  const std::string state_key = state->ToString();
  if (state_action_.find(state_key) == state_action_.end()) {
    state_action_[state_key] =
        std::vector<float>(actions_.size(), 0.0);
    return actions_.Random(state);
  }
  // Take the best possible action.
  // TODO(xavigonzalvo): even when we have already visited this state, it
  // sounds reasonable that we want to randomize actions even more.
  const std::vector<float> &action_scores = state_action_[state_key];
  const std::vector<int> actions = Sort(action_scores);
  for (int i = 0; i < actions.size(); ++i) {
    if (state->Valid(actions[i])) {
      return actions[i];
    }
  }
  // Something really bad happened at this point.
  std::cerr << "No valid actions could be taken, table:\n"
            << state->DebugString();
  return -1;
}

void BaseAgent::SetAction(const State *state) {
  state_id_ = state->id();
  action_ = SelectAction(state);
}

void BaseAgent::SetNextAction(const State *state) {
  next_state_id_ = state->id();
  next_action_ = SelectAction(state);
}

namespace {

class BiggerThanComparator {
 public:
  BiggerThanComparator(const std::vector<float> &v) : v_(v) {}

  bool operator()(int i1, int i2) {
    return v_[i1] > v_[i2];
  }

 private:
  const std::vector<float> v_;
};

}  // namespace

// Sorts a vector by value in decreasing order and returns the indices.
std::vector<int> BaseAgent::Sort(const std::vector<float> &v) const {
  std::vector<int> ids(v.size());
  for (int i = 0; i != ids.size(); ++i) {
    ids[i] = i;
  }
  sort(ids.begin(), ids.end(), BiggerThanComparator(v));
  return ids;
}

bool BaseAgent::Save(const std::string &filename) const {
  AgentModel model;
  for (StateActionMap::const_iterator it = state_action_.begin();
       it != state_action_.end();
       ++it) {
    AgentModel::State *state = model.add_states();
    state->set_key(it->first);
    for (int i = 0; i < it->second.size(); ++i) {
      state->add_action_scores(it->second[i]);
    }
  }
  std::fstream output(filename.c_str(),
                      std::ios::out | std::ios::trunc | std::ios::binary);
  if (!model.SerializeToOstream(&output)) {
    std::cerr << "Failed to write model from " << filename;
    return false;
  }
  return true;
}

bool BaseAgent::Load(const std::string &filename) {
  AgentModel model;
  std::fstream input(filename.c_str(), std::ios::in | std::ios::binary);
  if (!model.ParseFromIstream(&input)) {
    std::cerr << "Failed to load model from " << filename;
    return false;
  }
  std::vector<float> action_scores;
  for (int i = 0; i < model.states_size(); ++i) {
    action_scores.reserve(model.states(i).action_scores_size());
    for (int j = 0; j < model.states(i).action_scores_size(); ++j) {
      action_scores.push_back(model.states(i).action_scores(j));
    }
    state_action_[model.states(i).key()] = action_scores;
    action_scores.clear();
  }
  return true;
}

}  // namespace ttt
