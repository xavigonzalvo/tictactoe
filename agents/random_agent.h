// A random agents learns nothing and it purpose is pure exploration.

#ifndef TTT_AGENTS_RANDOM_AGENT_H_
#define TTT_AGENTS_RANDOM_AGENT_H_

#include "agents/base_agent.h"
#include "environment/state.h"
#include "environment/state_handler.h"

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

#endif  // TTT_AGENTS_RANDOM_AGENT_H_
