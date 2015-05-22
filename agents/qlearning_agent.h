// Agent using off-policy learning (ie. Q-learning).

#ifndef TTT_AGENTS_QLEARNING_AGENT_H_
#define TTT_AGENTS_QLEARNING_AGENT_H_

#include "agents/base_agent.h"
#include "environment/actions.h"
#include "environment/state.h"
#include "environment/state_handler.h"

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

#endif  // TTT_AGENTS_QLEARNING_AGENT_H_
