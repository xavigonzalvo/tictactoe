// Tic-Tac-Toe environment. Starts, runs and controls the game execution.

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_

#include "experimental/users/xavigonzalvo/ttt/agents/base_agent.h"
#include "experimental/users/xavigonzalvo/ttt/environment/environment.h"
#include "experimental/users/xavigonzalvo/ttt/environment/tictactoe_state.h"

namespace ttt {

class TicTacToeEnvironment : public Environment {
 public:
  static const int kTableDimension = 9;

  TicTacToeEnvironment(BaseAgent *opponent, StateHandler *state_handler)
      : Environment(opponent, state_handler),
        state_(kTableDimension) {}
  ~TicTacToeEnvironment() {}

  bool Start() override;

  bool Run(int action) override;

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

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ENVIRONMENT_H_
