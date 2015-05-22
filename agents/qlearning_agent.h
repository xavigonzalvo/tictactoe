// Agent using off-policy learning (ie. Q-learning).

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_QLEARNING_AGENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_QLEARNING_AGENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/actions.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"

namespace ttt {

class QLearningAgent : public BaseAgent {
 public:
  QLearningAgent(const Config &config, const Actions &actions,
                 const StateHandler &state_handler)
      : BaseAgent(config, actions, state_handler) {}
  ~QLearningAgent() override {}

  bool Update(float reward, bool last_state) override;
  void SetNextAction(const State *state) override;
};

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_QLEARNING_AGENT_H_
