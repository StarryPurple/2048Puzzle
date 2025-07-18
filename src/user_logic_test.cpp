#include "include/game_logic.h"
#include "include/user_logic.h"

#include <iostream>
#include <sstream>

using namespace PZ2048;

void SingleTest() {
  int row_num, col_num;
  uint seed;
  std::cin >> row_num >> col_num >> seed;

  ClientPrepare(row_num, col_num);
  Start(row_num, col_num, seed);
  while(true) {

    std::ostringstream oss;
    auto *obuf = std::cout.rdbuf(oss.rdbuf()); // redirect std::cout.

    PrintBoard();

    std::istringstream iss(oss.str());
    std::cout.rdbuf(obuf);                     // reset std:cout.
    auto *ibuf = std::cin.rdbuf(iss.rdbuf());  // redirect std::cin.

    ReadBoard();                               // read what PrintBoard() has output.

    std::cin.rdbuf(ibuf);                      // reset std::cin.

    char oper = Decide();
    // must be a valid move. No undo allowed. No Steins-Gate.
    if(oper != 'w' && oper != 's' && oper != 'a' && oper != 'd') {
      std::cout << " Invalid Operation.\n";
      continue;
    }

    TryRun(oper);

    /*
    if(flag) {
      std::cout << "Operation succeeded.\n";
    } else {
      std::cout << "Operation failed.\n";
    }
    std::cout << RowNum() << ' ' << ColNum() << ' ' << Steps() << ' ' << Score() << '\n';
    PrintBoard();
    */

    if(HasReachedTarget(2048)) {
      std::cout << "You've merged an 2048 tile!\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\n score: " << score << '\n';
      break;
    }
    if(Stuck()) {
      std::cout << "You've stuck.\n";
      auto [steps, score] = EndGame();
      std::cout << "Steps: " << steps << "\n score: " << score << '\n';
      break;
    }
  }
}

int main() {
  SingleTest();
  return 0;
}

