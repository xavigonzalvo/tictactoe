// Agent using on-policy learning (ie. Sarsa).

#ifndef TTT_AGENTS_SARSA_AGENT_H_
#define TTT_AGENTS_SARSA_AGENT_H_

#include "agents/base_agent.h"
#include "environment/actions.h"
#include "environment/state.h"
#include "environment/state_handler.h"
#include "environment/tictactoe_state.h"

namespace ttt {

class SarsaAgent : public BaseAgent {
 public:
  SarsaAgent(const Config &config, const Actions &actions,
             const StateHandler &state_handler)
      : BaseAgent(config, actions, state_handler) {}
  ~SarsaAgent() override {}

  bool Update(float reward, bool last_state) override;
};

}  // namespace ttt

#endif  // TTT_AGENTS_SARSA_AGENT_H_
