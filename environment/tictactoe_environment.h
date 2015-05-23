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
// Tic-Tac-Toe environment. Starts, runs and controls the game execution.

#ifndef TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_
#define TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_

#include "agents/base_agent.h"
#include "environment/environment.h"
#include "environment/tictactoe_state.h"

namespace ttt {

class TicTacToeEnvironment : public Environment {
 public:
  static const int kTableDimension = 9;

  TicTacToeEnvironment(BaseAgent *opponent, StateHandler *state_handler)
      : Environment(opponent, state_handler),
        state_(kTableDimension) {}
  ~TicTacToeEnvironment() {}

  bool Start(bool verbose);

  bool Run(int action);

  const State *state() const { return &state_; }

  // TODO(xavigonzalvo): move reward to state.
  float reward() const { return reward_; }

 private:
  // Current state of the table.
  TicTacToeState state_;

  // Current reward.
  float reward_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_
