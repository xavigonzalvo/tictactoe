// Tic-Tac-Toe actions. This creates all necessary actions for the game. No need
// to define a specific container for actions as the generic representation is
// enough. Look at actions.h for more information.

#ifndef TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_
#define TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_

#include "environment/actions.h"

namespace ttt {

void InitTicTacToeActions(Actions *actions, int num_actions) {
  for (int i = 0; i < num_actions; ++i) {
    actions->Add();
  }
}

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_
