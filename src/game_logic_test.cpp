#include "include/game_logic.h"

#include <iostream>

using namespace PZ2048;

void check_target(int &target) {
  if(target <= 4) {
    target = 8;
    std::cout << "Target too low. Automatically changed target to 8.\n";
    return;
  }
  if(target > 8192) {
    target = 8192;
    std::cout << "Target too large. Automatically changed target to 8192.\n";
    return;
  }
  int cnt = 0, tmp = target;
  while(tmp > 0) {
    cnt++;
    tmp >>= 1;
  }
  if(target != (1 << (cnt - 1))) {
    target = 1 << cnt;
    std::cout << "Target is not a power of 2. Automatically changed target to " << target << ".\n";
  }
}

int main() {
  int row_num, col_num, target;
  uint seed;
  std::cin >> row_num >> col_num >> target >> seed;
  check_target(target);

  Start(row_num, col_num, seed);
  int index = 0; // number of commands the user tried to operate
  std::cout << '[' << index << "] ";
  std::cout << "Steps: " << Steps() << " Score: " << Score() << '\n';
  PrintBoard();
  while(true) {
    char oper = std::cin.get();
    if(oper == ' ' || oper == '\n' || oper == '\r') continue;
    if(oper == EOF) break;
    if(oper == '#') break; // special control, can be used in command line tests.
    index++;
    std::cout << '[' << index << "] ";
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
      default:  std::cout << "Invalid operation.\n"; continue;
      }
      flag = TryRun(oper);
    }
    if(flag) {
      std::cout << " Operation succeeded.\n";
    } else {
      std::cout << " Operation failed.\n";
    }
    std::cout << "Steps: " << Steps() << " Score: " << Score() << '\n';
    PrintBoard();
    if(HasReachedTarget(target)) {
      std::cout << "You've merged a " << target << " tile!\n";
      break;
    }
    if(Stuck()) {
      std::cout << "You've stuck.\n";
      break;
    }
  }
  std::cout << "Game ended.\n";
  auto [steps, score] = EndGame();
  std::cout << "Steps: " << steps << "\n""Score: " << score << '\n';
  return 0;
}