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
#include "agents/human_agent.h"

#include <iostream>
#include <vector>

namespace ttt {

bool HumanAgent::Update(float reward, bool last_state) {
  // Intentionally left blank.
  state_id_ = next_state_id_;
  action_ = next_action_;
  return true;
}

void HumanAgent::SetAction(const State *state) {
  state_id_ = state->id();
  std::cout << state->DebugString() << "\nAction? [0-8] ";
  std::cin >> action_;
  while (!state->Valid(action_)) {
    std::cout << "\nSpecify a valid action [0-8]: ";
    std::cin >> action_;
  }
}

void HumanAgent::SetNextAction(const State *state) {
  next_state_id_ = state->id();
  std::cout << state->DebugString() << "\nAction [0-8]: ";
  std::cin >> next_action_;
  while (!state->Valid(next_action_)) {
    std::cout << "\nSpecify a valid action [0-8]: ";
    std::cin >> next_action_;
  }
}

}  // namespace ttt
