#include "agents/base_agent.h"

#include <algorithm>

#include "file/base/file.h"
#include "file/base/helpers.h"
#include "util/gtl/map_util.h"
#include "agents/agent_model.pb.h"

namespace ttt {

BaseAgent::BaseAgent(const Config &config, const Actions &actions,
                     const StateHandler &state_handler)
    : config_(config), actions_(actions), state_handler_(state_handler),
      random_(ACMRandom::HostnamePidTimeSeed()) {
}

int BaseAgent::SelectAction(const State *state) {
  // Explore random action.
  if (random_.RndFloat() < config_.epsilon()) {
    return actions_.Random(state);
  }
  // If not present, randomize action and insert empty scores.
  const string state_key = state->ToString();
  if (!ContainsKey(state_action_, state_key)) {
    LookupOrInsert(&state_action_, state_key,
                   vector<float>(actions_.size(), 0.0));
    return actions_.Random(state);
  }
  // Take the best possible action.
  // TODO(xavigonzalvo): even when we have already visited this state, it
  // sounds reasonable that we want to randomize actions even more.
  const vector<float> &action_scores = FindOrDie(state_action_, state_key);
  const vector<int> actions = Sort(action_scores);
  for (int i = 0; i < actions.size(); ++i) {
    if (state->Valid(actions[i])) {
      return actions[i];
    }
  }
  // Something really bad happened at this point.
  LOG(FATAL) << "No valid actions could be taken, table:\n"
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

// Sorts a vector by value in decreasing order and returns the indices.
vector<int> BaseAgent::Sort(const vector<float> &v) const {
  vector<int> ids(v.size());
  for (int i = 0; i != ids.size(); ++i) {
    ids[i] = i;
  }
  sort(ids.begin(), ids.end(),
       [&v](int i1, int i2) {return v[i1] > v[i2];});
  return ids;
}

bool BaseAgent::Save(const string &filename) const {
  AgentModel model;
  for (auto it = state_action_.begin(); it != state_action_.end(); ++it) {
    auto *state = model.add_states();
    state->set_key(it->first);
    for (int i = 0; i < it->second.size(); ++i) {
      state->add_action_scores(it->second[i]);
    }
  }
  return file::SetBinaryProto(filename, model, file::Defaults()).ok();
}

bool BaseAgent::Load(const string &filename) {
  AgentModel model;
  if (!file::GetBinaryProto(filename, &model, file::Defaults()).ok()) {
    LOG(ERROR) << "Failed to load model from " << filename;
    return false;
  }
  vector<float> action_scores;
  for (int i = 0; i < model.states_size(); ++i) {
    action_scores.reserve(model.states(i).action_scores_size());
    for (int j = 0; j < model.states(i).action_scores_size(); ++j) {
      action_scores.push_back(model.states(i).action_scores(j));
    }
    InsertOrDie(&state_action_, model.states(i).key(), action_scores);
    action_scores.clear();
  }
  return true;
}

}  // namespace ttt
