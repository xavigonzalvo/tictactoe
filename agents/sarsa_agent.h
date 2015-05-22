// Agent using on-policy learning (ie. Sarsa).

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_SARSA_AGENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_SARSA_AGENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/actions.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"
#include "experimental/users/xavigonzalvo/ttt/environment/tictactoe_state.h"

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

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_SARSA_AGENT_H_
