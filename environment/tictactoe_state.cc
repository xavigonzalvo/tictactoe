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
#include "environment/tictactoe_state.h"

#include <iostream>
#include <stdio.h>

namespace ttt {

namespace {

// A simple matrix to handle the table in a readable matrix way.
class SimpleMatrix {
 public:
  // Creates a simple square matrix.
  SimpleMatrix(const std::string &data, int size)
      : data_(data.c_str()), size_(size) {}

  char at(int row, int col) const {
    return data_[row * size_ + col];
  }

 private:
  const char *data_;
  const int size_;
};

}  // namespace

bool TicTacToeState::Init(bool verbose) {
  if (!State::Init()) {
    return false;
  }
  table_.clear();
  table_.resize(dimension_, kEmptyPosition);
  verbose_ = verbose;
  return true;
}

bool TicTacToeState::Valid(int action) const {
  if (action >= dimension_ || action < 0) {
    return false;
  }
  return table_[action] == kEmptyPosition;
}

bool TicTacToeState::Do(int action, bool opponent, float *reward) {
  if (!Valid(action)) {
    std::cerr << "Invalid action";
    return false;
  }
  num_actions_++;
  table_[action] = opponent ? 'O' : 'X';
  if (SomebodyWon(verbose_)) {
    finished_ = true;
    if (!opponent) {
      *reward = kSuccessReward;
    } else {
      *reward = kFailureReward;
    }
  } else {
    finished_ = (num_actions_ >= dimension_);
    *reward = kInGameReward;
  }
  return true;
}

// Although it is somehow generic it only checks for the diagonals of
// a 3x3 table.
bool TicTacToeState::SomebodyWon(bool verbose) const {
  if (num_actions_ < (2 * num_rows_ - 1)) {
    // We need at least 5 actions in a 3x3 table to be in a potential final
    // state where the two players have played enough number of times.
    return false;
  }
  bool success = false;
  SimpleMatrix matrix(table_, num_rows_);
  // Horizontals.
  for (int row = 0; row < num_rows_; ++row) {
    success = true;
    for (int col = 0; col < num_rows_; ++col) {
      if (matrix.at(row, col) == kEmptyPosition) {
        success = false;
        break;
      }
      success &= (matrix.at(row, col) == matrix.at(row, 0));
    }
    if (success) {
      if (verbose) std::cout << "Horizontal";
      return true;
    }
  }
  // Verticals.
  for (int col = 0; col < num_rows_; ++col) {
    success = true;
    for (int row = 0; row < num_rows_; ++row) {
      if (matrix.at(row, col) == kEmptyPosition) {
        success = false;
        break;
      }
      success &= (matrix.at(row, col) == matrix.at(0, col));
    }
    if (success) {
      if (verbose) std::cout << "Vertical";
      return true;
    }
  }
  // Left diagonal.
  success = true;
  for (int i = 0; i < num_rows_; ++i) {
    if (matrix.at(i, i) == kEmptyPosition) {
      success = false;
      break;
    }
    success &= (matrix.at(i, i) == matrix.at(0, 0));
  }
  if (success) {
    if (verbose) std::cout << "Left diagonal";
    return true;
  }
  // Right diagonal.
  success = true;
  for (int i = num_rows_ - 1; i >= 0; --i) {
    if (matrix.at(num_rows_ - 1 - i, i) == kEmptyPosition) {
      success = false;
      break;
    }
    success &= (matrix.at(num_rows_ - 1 - i, i) == matrix.at(0, num_rows_ - 1));
  }
  if (success) {
    if (verbose) std::cout << "Right diagonal";
    return true;
  }
  return false;
}

std::string TicTacToeState::DebugString() const {
  char buffer[33];
  snprintf(buffer, sizeof(buffer), "%d", num_actions_);
  std::string ret = std::string("final_state: ") +
      (finished_ ? "true" : "false") +
      " num_actions: " + std::string(buffer) + "\n";
  SimpleMatrix matrix(table_, num_rows_);
  for (int i = 0; i < num_rows_; ++i) {
    for (int j = 0; j < num_rows_; ++j) {
      ret += " " + std::string(1, matrix.at(i, j));
    }
    ret += "\n";
  }
  return ret;
}

}  // namespace ttt
