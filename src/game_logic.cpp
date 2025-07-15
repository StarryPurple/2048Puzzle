#include "include/game_logic.h"

#include <iomanip>
#include <iostream>

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Or... can you?
// Just don't modify the signatures of existing functions.

// Don't try to use extern variables from user_logic.cpp. You're not supposed to communicate through this way.
// After all, the game logic on the online judger won't contain extern variables same as yours.

inline int rows, cols, steps, score, prev_steps, prev_score;
inline std::vector<std::vector<int>> board, prev_board;
inline bool prev_valid;

// You are free to add helper functions.

void Start(int row_num, int col_num, uint game_seed) {
  srand(game_seed); // Should be the PZ2048::srand(uint).
  rows = row_num;
  cols = col_num;

  // You may want to add more lines.
  steps = 0;
  score = 0;
  board.clear();
  board.resize(rows, std::vector<int>(cols));
  prev_board.resize(rows, std::vector<int>(cols));
  prev_valid = false;

  TryGenerateTile();
}

std::pair<int, int> EndGame() {
  /** implementation here **/
  return {steps, score};
}

int GetRows() { return rows; }

int GetCols() { return cols; }

bool TryRunW() {
  static std::vector<int> arr;
  bool valid = false;
  for(int j = 0; j < cols; j++) {
    arr.clear();
    arr.resize(rows);
    int t = 0;
    for(int i = 0; i < rows; i++)
      if(board[i][j] > 0) arr[t++] = board[i][j];
    for(int i = 0; i + 1 < t; i++)
      if(arr[i] == arr[i + 1]) {
        arr[i] *= 2;
        score += arr[i];
        for(int k = i + 1; k < t - 1; k++)
          arr[k] = arr[k + 1];
        arr[--t] = 0;
      }
    for(int i = 0; i < rows; i++) {
      if(arr[i] != board[i][j]) {
        if(!valid) {
          prev_board = board;
          prev_score = score;
          prev_steps = steps;
          prev_valid = true;
        }
        valid = true;
        board[i][j] = arr[i];
      }
    }
  }
  return valid;
}

bool TryRunS() {
  static std::vector<int> arr;
  bool valid = false;
  for(int j = 0; j < cols; j++) {
    arr.clear();
    arr.resize(rows);
    int t = rows - 1;
    for(int i = rows - 1; i >= 0; i--)
      if(board[i][j] > 0) arr[t--] = board[i][j];
    for(int i = rows - 1; i - 1 > t; i--)
      if(arr[i] == arr[i - 1]) {
        arr[i] *= 2;
        score += arr[i];
        for(int k = i - 1; k > t + 1; k--)
          arr[k] = arr[k - 1];
        arr[++t] = 0;
      }
    for(int i = rows - 1; i >= 0; i--) {
      if(arr[i] != board[i][j]) {
        if(!valid) {
          prev_board = board;
          prev_score = score;
          prev_steps = steps;
          prev_valid = true;
        }
        valid = true;
        board[i][j] = arr[i];
      }
    }
  }
  return valid;
}

bool TryRunA() {
  static std::vector<int> arr;
  bool valid = false;
  for(int i = 0; i < rows; i++) {
    arr.clear();
    arr.resize(cols);
    int t = 0;
    for(int j = 0; j < cols; j++)
      if(board[i][j] > 0) arr[t++] = board[i][j];
    for(int j = 0; j + 1 < t; j++)
      if(arr[j] == arr[j + 1]) {
        arr[j] *= 2;
        score += arr[j];
        for(int k = j + 1; k < t - 1; k++)
          arr[k] = arr[k + 1];
        arr[--t] = 0;
      }
    for(int j = 0; j < cols; j++) {
      if(arr[j] != board[i][j]) {
        if(!valid) {
          prev_board = board;
          prev_score = score;
          prev_steps = steps;
          prev_valid = true;
        }
        valid = true;
        board[i][j] = arr[j];
      }
    }
  }
  return valid;
}

bool TryRunD() {
  static std::vector<int> arr;
  bool valid = false;
  for(int i = 0; i < rows; i++) {
    arr.clear();
    arr.resize(cols);
    int t = cols - 1;
    for(int j = cols - 1; j >= 0; j--)
      if(board[i][j] > 0) arr[t--] = board[i][j];
    for(int j = cols - 1; j - 1 > t; j--)
      if(arr[j] == arr[j - 1]) {
        arr[j] *= 2;
        score += arr[j];
        for(int k = j - 1; k > t + 1; k--)
          arr[k] = arr[k - 1];
        arr[++t] = 0;
      }
    for(int j = cols - 1; j >= 0; j--) {
      if(arr[j] != board[i][j]) {
        if(!valid) {
          prev_board = board;
          prev_score = score;
          prev_steps = steps;
          prev_valid = true;
        }
        valid = true;
        board[i][j] = arr[j];
      }
    }
  }
  return valid;
}

bool TryRun(char dir) {
  /** implementation here **/
  bool valid = false;
  switch(dir) {
  case 'w': valid = TryRunW(); break;
  case 's': valid = TryRunS(); break;
  case 'a': valid = TryRunA(); break;
  case 'd': valid = TryRunD(); break;
  default: break;
  }
  if(valid) {
    steps++;
    TryGenerateTile();
  }
  return valid;
}

bool Undo() {
  if(!prev_valid) return false;
  board = prev_board;
  score = prev_score;
  steps = prev_steps;
  prev_valid = false;
  return true;
}

void SetTile(int row_index, int col_index, int value) {
  board[row_index][col_index] = value;
}

int GetTile(int row_index, int col_index) {
  return board[row_index][col_index];
}

int Score() { return score; }

int Steps() { return steps; }

bool HasReachedTarget(int target) {
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      if(board[i][j] >= target) {
        return true;
      }
  return false;
}

bool Stuck() {
  /** implementation here **/
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols; j++)
      if(board[i][j] == 0)
        return false;
  for(int i = 0; i < rows - 1; i++)
    for(int j = 0; j < cols; j++)
      if(board[i][j] == board[i + 1][j])
        return false;
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cols - 1; j++)
      if(board[i][j] == board[i][j + 1])
        return false;
  return true;
}

void PrintBoard() {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < cols; j++) {
      std::cout << std::left << std::setw(4) << board[i][j];
      if(j != cols - 1) std::cout << ' ';
    }
    if(i != rows) std::cout << '\n';
  }
}

}