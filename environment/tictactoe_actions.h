// Tic-Tac-Toe actions. This creates all necessary actions for the game. No need
// to define a specific container for actions as the generic representation is
// enough. Look at actions.h for more information.

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_

#include "experimental/users/xavigonzalvo/ttt/environment/actions.h"

namespace ttt {

void InitTicTacToeActions(Actions *actions, int num_actions) {
  for (int i = 0; i < num_actions; ++i) {
    actions->Add();
  }
}

}  // namespace ttt

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_TICTACTOE_ACTIONS_H_
