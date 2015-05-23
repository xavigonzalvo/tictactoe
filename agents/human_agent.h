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
  ~HumanAgent() {}

  void SetAction(const State *state);
  void SetNextAction(const State *state);
  bool Update(float reward, bool last_state);

  bool human() const { return true; }
};

}  // namespace ttt

#endif  // TTT_AGENTS_HUMAN_AGENT_H_
