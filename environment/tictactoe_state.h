// State handler for the Tic-Tac-Toe game. The world is represented as
// a string where main player uses "X" symbols and the opponent uses
// "O".

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_STATE_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_STATE_H_

#include <math.h>
#include <string>

#include "experimental/users/xavigonzalvo/ttt/environment/state.h"

namespace ttt {

class TicTacToeState : public State {
 public:
  static const int kSuccessReward = 1;
  static const int kFailureReward = -1;
  static const int kInGameReward = 0;

  explicit TicTacToeState(int dimension)
      : State(dimension), num_rows_(sqrt(dimension_)) {}

  bool Init() override;

  bool Valid(int action) const override;

  // Does an action in the tic-tac-toe table. It sets an "X" for the
  // main player and a "O" for the opponent.
  bool Do(int action, bool opponent, float *reward) override;

  // Returns a string representation of the state to use in a q-table.
  string ToString() const override { return table_; }

  // Returns a readable Tic-Tac-Toe table.
  string DebugString() const override;

 protected:
  // Returns true if somebody has won the game.
  bool SomebodyWon() const;

 private:
  // The data for the tictactoe table. Each char represents a position of the
  // table. Main player uses "X" and opponent "O".
  string table_;
  static const char kEmptyPosition = '.';

  // Number of rows of the table.
  const int num_rows_;
};

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_STATE_H_
