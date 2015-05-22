#include "agents/agent_factory.h"

#include "agents/human_agent.h"
#include "agents/random_agent.h"
#include "agents/sarsa_agent.h"
#include "agents/qlearning_agent.h"

namespace ttt {

BaseAgent *AgentFactory(const std::string &name,
                        const Config &config, const Actions &actions,
                        const StateHandler &state_handler) {
  if (name == "RandomAgent") {
    return new RandomAgent(config, actions, state_handler);
  } else if (name == "HumanAgent") {
    return new HumanAgent(config, actions, state_handler);
  } else if (name == "SarsaAgent") {
    return new SarsaAgent(config, actions, state_handler);
  } else if (name == "QLearningAgent") {
    return new QLearningAgent(config, actions, state_handler);
  }
  std::cerr << "Agent \"" << name << "\" doesn't exist";
  return NULL;
}

}  // namespace ttt
