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
#include "environment/tictactoe_environment.h"

namespace ttt {

bool TicTacToeEnvironment::Start(bool verbose) {
  end_of_episode_ = false;
  if (!state_.Init(verbose)) {
    return false;
  }
  state_handler_->Clear();
  state_handler_->Add(&state_);
  return true;
}

bool TicTacToeEnvironment::Run(int action) {
  // Main player's move.
  if (!state_.Do(action, false /* learner agent */, &reward_)) {
    std::cerr << "Failed to execute action of main player: " << action
              << " table: " << state_.DebugString();
    return false;
  }
  state_.NextId();
  state_handler_->Add(&state_);
  if (state_.finished()) {
    end_of_episode_ = true;
    return true;
  }
  // Opponent's move.
  opponent_->SetAction(&state_);
  if (!state_.Do(opponent_->action(), true /* opponent agent */, &reward_)) {
    std::cerr << "Failed to execute action of opponent: "
              << opponent_->action() << " table: " << state_.DebugString();
    return false;
  }
  state_.NextId();
  state_handler_->Add(&state_);
  if (state_.finished()) {
    end_of_episode_ = true;
    return true;
  }
  return true;
}

}  // namespace ttt
