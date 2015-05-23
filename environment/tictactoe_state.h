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

  bool Init(bool verbose);

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
  bool SomebodyWon(bool verbose) const;

 private:
  // The data for the tictactoe table. Each char represents a position of the
  // table. Main player uses "X" and opponent "O".
  std::string table_;
  static const char kEmptyPosition = '.';

  // Number of rows of the table.
  int num_rows_;

  bool verbose_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_TICTACTOE_STATE_H_
