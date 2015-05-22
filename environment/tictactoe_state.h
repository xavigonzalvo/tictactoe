// State handler for the Tic-Tac-Toe game. The world is represented as
// a std::string where main player uses "X" symbols and the opponent uses
// "O".

#ifndef TTT_ENVIRONMENT_TICTACTOE_STATE_H_
#define TTT_ENVIRONMENT_TICTACTOE_STATE_H_

#include <math.h>
#include <string>

#include "environment/state.h"

namespace ttt {

class TicTacToeState : public State {
 public:
  static const int kSuccessReward = 1;
  static const int kFailureReward = -1;
  static const int kInGameReward = 0;

  explicit TicTacToeState(int dimension)
      : State(dimension), num_rows_(sqrt(dimension_)) {}

  bool Init();

  bool Valid(int action) const;

  // Does an action in the tic-tac-toe table. It sets an "X" for the
  // main player and a "O" for the opponent.
  bool Do(int action, bool opponent, float *reward);

  // Returns a std::string representation of the state to use in a q-table.
  std::string ToString() const { return table_; }

  // Returns a readable Tic-Tac-Toe table.
  std::string DebugString() const;

 protected:
  // Returns true if somebody has won the game.
  bool SomebodyWon() const;

 private:
  // The data for the tictactoe table. Each char represents a position of the
  // table. Main player uses "X" and opponent "O".
  std::string table_;
  static const char kEmptyPosition = '.';

  // Number of rows of the table.
  int num_rows_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_TICTACTOE_STATE_H_
