#include "include/user_logic.h"

#include "include/utils.h"
#include "include/game_logic.h"

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Just don't modify the signatures of existing functions.

// You are free to add helper functions.

// Don't try to use extern variables from game_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.

void ClientPrepare(int row_num, int col_num) {
  /** implement here. **/
}

void ReadBoard() {
  /** implement here. **/
}

char Decide() {
  /** implement here. **/
  return 'w';
}


}