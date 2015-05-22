// A random agents learns nothing and it purpose is pure exploration.

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_RANDOM_AGENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_RANDOM_AGENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"

namespace ttt {

class RandomAgent : public BaseAgent {
 public:
  RandomAgent(const Config &config, const Actions &actions,
              const StateHandler &state_handler)
      : BaseAgent(config, actions, state_handler) {}
  ~RandomAgent() override {}

  void SetAction(const State *state) override;
  void SetNextAction(const State *state) override;
  bool Update(float reward, bool last_state) override;
};

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_RANDOM_AGENT_H_
