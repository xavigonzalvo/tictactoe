// Main action handler. This class is generic so no further definitions should
// be required. Have a look at tictactoe_actions.h to see and example.
//
// Usage:
//    Actions actions;
//    for (int i = 0; i < ACTIONS; ++i)
//      actions.Add();

#ifndef TTT_ENVIRONMENT_ACTIONS_H_
#define TTT_ENVIRONMENT_ACTIONS_H_

#include <vector>

#include "environment/state.h"
#include "util/random/acmrandom.h"

namespace ttt {

class Actions {
 public:
  Actions() : size_(0), random_(ACMRandom::HostnamePidTimeSeed()) {}
  ~Actions() {}

  // Returns the number of actions.
  int size() const;

  // Returns a random action.
  int Random(const State *state) const;

  // Adds a new action and returns its integer id.
  int Add();

 private:
  // Number of actions.
  int size_;

  // Random number generator for the random action selection in
  // exploratory mode.
  mutable ACMRandom random_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_ACTIONS_H_
