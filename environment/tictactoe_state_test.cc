// Unit test for the Tic-Tac-Toe state handler.

#include "environment/tictactoe_state.h"

#include "testing/base/public/gunit.h"

namespace ttt {
namespace {

const int kDim = 9;

class TicTacToeStateAccessor : public TicTacToeState {
 public:
  explicit TicTacToeStateAccessor(int dim) : TicTacToeState(dim) {}

 private:
  FRIEND_TEST(TictactoeStateTest, DoActions);
  FRIEND_TEST(TictactoeStateTest, Finished);
};

class TictactoeStateTest : public ::testing::Test {
 protected:
  TictactoeStateTest() : state_(kDim) {}

  void SetUp() override {
    ASSERT_TRUE(state_.Init());
  }

  TicTacToeStateAccessor state_;
};

TEST_F(TictactoeStateTest, DoActions) {
  float reward;
  // Expected failures.
  ASSERT_FALSE(state_.Do(-1, false, &reward));
  ASSERT_FALSE(state_.Do(9, false, &reward));
  ASSERT_FALSE(state_.Do(10, false, &reward));

  // Expected success.
  const std::vector<std::string> kTables = {
    "X........",
    ".X.......",
    "..X......",
    "...X.....",
    "....X....",
    ".....X...",
    "......X..",
    ".......X.",
    "........X",
  };
  for (int i = 0; i < kDim; ++i) {
    ASSERT_TRUE(state_.Init());
    ASSERT_TRUE(state_.Do(i, false, &reward));
    EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
    EXPECT_EQ(kTables[i], state_.ToString());
  }
  // Random positions.
  ASSERT_TRUE(state_.Init());

  ASSERT_TRUE(state_.Do(3, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ("...X.....", state_.ToString());

  ASSERT_TRUE(state_.Do(6, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ("...X..O..", state_.ToString());

  ASSERT_TRUE(state_.Do(8, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ("...X..O.O", state_.ToString());

  ASSERT_TRUE(state_.Do(7, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ("...X..OXO", state_.ToString());

  ASSERT_TRUE(state_.Do(4, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ("...XX.OXO", state_.ToString());

  ASSERT_TRUE(state_.Do(1, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kInGameReward, reward);
  EXPECT_EQ(".O.XX.OXO", state_.ToString());
}

TEST_F(TictactoeStateTest, Finished) {
  float reward;
  // Vertical 1.
  ASSERT_TRUE(state_.Do(0, true, &reward));
  ASSERT_TRUE(state_.Do(1, false, &reward));
  ASSERT_TRUE(state_.Do(3, true, &reward));
  ASSERT_TRUE(state_.Do(2, false, &reward));
  ASSERT_TRUE(state_.Do(6, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kFailureReward, reward);
  EXPECT_EQ("OXXO..O..", state_.ToString());
  // Vertical 2.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(1, true, &reward));
  ASSERT_TRUE(state_.Do(0, false, &reward));
  ASSERT_TRUE(state_.Do(4, true, &reward));
  ASSERT_TRUE(state_.Do(2, false, &reward));
  ASSERT_TRUE(state_.Do(7, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kFailureReward, reward);
  EXPECT_EQ("XOX.O..O.", state_.ToString());
  // Vertical 3.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(2, true, &reward));
  ASSERT_TRUE(state_.Do(0, false, &reward));
  ASSERT_TRUE(state_.Do(5, true, &reward));
  ASSERT_TRUE(state_.Do(1, false, &reward));
  ASSERT_TRUE(state_.Do(8, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kFailureReward, reward);
  EXPECT_EQ("XXO..O..O", state_.ToString());
  // Horizontal 1.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(0, false, &reward));
  ASSERT_TRUE(state_.Do(7, true, &reward));
  ASSERT_TRUE(state_.Do(1, false, &reward));
  ASSERT_TRUE(state_.Do(8, true, &reward));
  ASSERT_TRUE(state_.Do(2, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kSuccessReward, reward);
  EXPECT_EQ("XXX....OO", state_.ToString());
  // Horizontal 2.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(3, false, &reward));
  ASSERT_TRUE(state_.Do(1, true, &reward));
  ASSERT_TRUE(state_.Do(4, false, &reward));
  ASSERT_TRUE(state_.Do(8, true, &reward));
  ASSERT_TRUE(state_.Do(5, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kSuccessReward, reward);
  EXPECT_EQ(".O.XXX..O", state_.ToString());
  // Horizontal 3.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(6, false, &reward));
  ASSERT_TRUE(state_.Do(1, true, &reward));
  ASSERT_TRUE(state_.Do(7, false, &reward));
  ASSERT_TRUE(state_.Do(3, true, &reward));
  ASSERT_TRUE(state_.Do(8, false, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kSuccessReward, reward);
  EXPECT_EQ(".O.O..XXX", state_.ToString());
  // Diagonal 1.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(0, true, &reward));
  ASSERT_TRUE(state_.Do(1, false, &reward));
  ASSERT_TRUE(state_.Do(4, true, &reward));
  ASSERT_TRUE(state_.Do(2, false, &reward));
  ASSERT_TRUE(state_.Do(8, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kFailureReward, reward);
  EXPECT_EQ("OXX.O...O", state_.ToString());
  // Diagonal 2.
  ASSERT_TRUE(state_.Init());
  ASSERT_TRUE(state_.Do(2, true, &reward));
  ASSERT_TRUE(state_.Do(1, false, &reward));
  ASSERT_TRUE(state_.Do(4, true, &reward));
  ASSERT_TRUE(state_.Do(8, false, &reward));
  ASSERT_TRUE(state_.Do(6, true, &reward));
  EXPECT_FLOAT_EQ(TicTacToeState::kFailureReward, reward);
  EXPECT_EQ(".XO.O.O.X", state_.ToString());
}

}  // namespace
}  // namespace ttt
