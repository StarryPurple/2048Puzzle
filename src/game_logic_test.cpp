#include "include/game_logic.h"

#include <iostream>

using namespace PZ2048;

int main() {
  int row_num, col_num;
  uint seed;
  std::string input;
  std::cin >> row_num >> col_num >> seed >> input;

  Start(row_num, col_num, seed);
  PrintBoard();
  for(char oper: input) {
    bool flag;
    if(oper == 'z') {
      std::cout << "Tried to undo previous operation.";
      flag = Undo();
    } else {
      switch(oper) {
      case 'w': std::cout << "Swiped upward.";     break;
      case 'a': std::cout << "Swiped leftward.";   break;
      case 's': std::cout << "Swiped downward.";   break;
      case 'd': std::cout << "Swiped rightward.";  break;
      default:  std::cout << "Invalid operation."; continue;
      }
      flag = TryRun(oper);
    }
    if(flag) {
      std::cout << " Operation succeeded.\n";
    } else {
      std::cout << " Operation failed.\n";
    }
    std::cout << GetRows() << ' ' << GetCols() << ' ' << Steps() << ' ' << Score() << '\n';
    PrintBoard();
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
  return 0;
}