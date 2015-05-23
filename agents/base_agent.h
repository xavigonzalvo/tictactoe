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
// Base class for an agent definition. Inherit from this class to implement
// your own learning method. You need to implement "Update" and optionally,
// SetAction and SetNextAction too.

#ifndef TTT_AGENTS_BASE_AGENT_H_
#define TTT_AGENTS_BASE_AGENT_H_

#include <map>
#include <string>
#include <vector>

#include "config.pb.h"
#include "core/simple_random.h"
#include "environment/actions.h"
#include "environment/state.h"
#include "environment/state_handler.h"

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
  bool Save(const std::string &filename) const;

  // Loads the agent memory from file.
  bool Load(const std::string &filename);

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
  std::vector<int> Sort(const std::vector<float> &v) const;

  const Config &config_;
  const Actions &actions_;
  const StateHandler &state_handler_;

  // State-action pair matrix. This is the $Q$ matrix in a Q-learning
  // algorithm.
  typedef std::map<std::string, std::vector<float> > StateActionMap;
  StateActionMap state_action_;

  // Current and next state.
  int state_id_;
  int next_state_id_;

  // Current and next action.
  int action_;
  int next_action_;

 private:
  SimpleRandom random_;
};

}  // namespace ttt

#endif  // TTT_AGENTS_BASE_AGENT_H_
