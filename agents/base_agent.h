// Base class for an agent definition. Inherit from this class to implement
// your own learning method. You need to implement "Update" and optionally,
// SetAction and SetNextAction too.

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_BASE_AGENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_BASE_AGENT_H_

#include <hash_map>
#include <string>
#include <vector>

#include "experimental/users/xavigonzalvo/ttt/config.pb.h"
#include "experimental/users/xavigonzalvo/ttt/environment/actions.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"
#include "util/random/acmrandom.h"
#include "util/registration/registerer.h"

namespace ttt {

class BaseAgent {
 public:
  virtual ~BaseAgent() {}

  // Set the current and next actions.
  virtual void SetAction(const State *state);
  virtual void SetNextAction(const State *state);

  // Update the q-table.
  virtual bool Update(float reward, bool last_state) = 0;

  // Returns the current action.
  int action() const { return action_; }

  // Saves the agent memory to file.
  bool Save(const string &filename) const;

  // Loads the agent memory from file.
  bool Load(const string &filename);

  // Returns true if it's a human agent.
  virtual bool human() const { return false; }

  // Returns the number of states.
  int NumStates() const { return state_action_.size(); }

 protected:
  BaseAgent(const Config &config, const Actions &actions,
            const StateHandler &state_handler);

  // Returns and action exploring or exploiting.
  int SelectAction(const State *state);

  // Sorts a vector by value in decreasing order and returns the indices.
  vector<int> Sort(const vector<float> &v) const;

  const Config &config_;
  const Actions &actions_;
  const StateHandler &state_handler_;

  // State-action pair matrix. This is the $Q$ matrix in a Q-learning
  // algorithm.
  hash_map<string, vector<float> > state_action_;

  // Current and next state.
  int state_id_;
  int next_state_id_;

  // Current and next action.
  int action_;
  int next_action_;

 private:
  ACMRandom random_;
};

DEFINE_REGISTERER_3(BaseAgent, const Config &, const Actions &,
                    const StateHandler &);
#define REGISTER_AGENT(name) REGISTER_ENTITY(name, BaseAgent);

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_BASE_AGENT_H_
