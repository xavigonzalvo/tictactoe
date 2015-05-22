// Human agent has the interface to ask an actual user which actions to perform.
// No learning is performed.

#ifndef TTT_AGENTS_HUMAN_AGENT_H_
#define TTT_AGENTS_HUMAN_AGENT_H_

#include "agents/base_agent.h"
#include "environment/actions.h"
#include "environment/state.h"
#include "environment/state_handler.h"

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

#endif  // TTT_AGENTS_HUMAN_AGENT_H_
