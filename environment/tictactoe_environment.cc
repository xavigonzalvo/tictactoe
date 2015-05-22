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
