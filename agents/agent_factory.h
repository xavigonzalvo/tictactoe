#include <string>

#include "agents/base_agent.h"
#include "config.pb.h"
#include "environment/actions.h"
#include "environment/state_handler.h"

namespace ttt {

BaseAgent *AgentFactory(const std::string &name,
                        const Config &config, const Actions &actions,
                        const StateHandler &state_handler);

}  // namespace ttt
