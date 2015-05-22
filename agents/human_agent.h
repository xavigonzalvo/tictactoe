// Human agent has the interface to ask an actual user which actions to perform.
// No learning is performed.

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_HUMAN_AGENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_HUMAN_AGENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/actions.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state.h"
#include "experimental/users/xavigonzalvo/ttt/environment/state_handler.h"

namespace ttt {

class HumanAgent : public BaseAgent {
 public:
  HumanAgent(const Config &config, const Actions &actions,
             const StateHandler &state_handler)
      : BaseAgent(config, actions, state_handler) {}
  ~HumanAgent() override {}

  void SetAction(const State *state) override;
  void SetNextAction(const State *state) override;
  bool Update(float reward, bool last_state) override;

  bool human() const override { return true; }
};

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_AGENTS_HUMAN_AGENT_H_
