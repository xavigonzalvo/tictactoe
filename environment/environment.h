// Generic environment class. Inherit from this class to create your own
// environment and implement the following methods:
//   - Start
//   - Run

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_ENVIRONMENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_ENVIRONMENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"

namespace ttt {

class Environment {
 public:
  virtual ~Environment() {}

  virtual bool Start() = 0;
  virtual bool Run(int action) = 0;

  // Returns true if it's the end of an episode.
  bool end_of_episode() const { return end_of_episode_; }

 protected:
  Environment(BaseAgent *opponent, StateHandler *state_handler)
      : opponent_(opponent), state_handler_(state_handler),
        end_of_episode_(false) {}

  BaseAgent *opponent_;
  StateHandler *state_handler_;

  // True when the episode has finished.
  bool end_of_episode_;
};

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_ENVIRONMENT_H_
