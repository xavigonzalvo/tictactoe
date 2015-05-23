/*
The MIT License (MIT)

Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
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
  std::cerr << "Agent \"" << name << "\" doesn't exist" << std::endl;
  return NULL;
}

}  // namespace ttt
