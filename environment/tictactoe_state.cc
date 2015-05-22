#include "experimental/users/xavigonzalvo/ttt/environment/tictactoe_state.h"

#include "base/logging.h"
#include "strings/stringpiece.h"
#include "strings/strcat.h"

namespace ttt {

namespace {

// A simple matrix to handle the table in a readable matrix way.
class SimpleMatrix {
 public:
  // Creates a simple square matrix.
  SimpleMatrix(const string &data, int size) : data_(data), size_(size) {}

  char at(int row, int col) const {
    return data_[row * size_ + col];
  }

 private:
  StringPiece data_;
  const int size_;
};

}  // namespace

bool TicTacToeState::Init() {
  if (!State::Init()) {
    return false;
  }
  table_.clear();
  table_.resize(dimension_, kEmptyPosition);
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
    LOG(ERROR) << "Invalid action";
    return false;
  }
  num_actions_++;
  table_[action] = opponent ? 'O' : 'X';
  if (SomebodyWon()) {
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
bool TicTacToeState::SomebodyWon() const {
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
      VLOG(1) << "Horizontal";
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
      VLOG(1) << "Vertical";
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
    VLOG(1) << "Left diagonal";
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
    VLOG(1) << "Right diagonal";
    return true;
  }
  return false;
}

string TicTacToeState::DebugString() const {
  string ret = StrCat("final_state: ", finished_ ? "true" : "false",
                      " num_actions: ", num_actions_, "\n");
  SimpleMatrix matrix(table_, num_rows_);
  for (int i = 0; i < num_rows_; ++i) {
    for (int j = 0; j < num_rows_; ++j) {
      StrAppend(&ret, " " , string(1, matrix.at(i, j)));
    }
    StrAppend(&ret, "\n");
  }
  return ret;
}

}  // namespace ttt
