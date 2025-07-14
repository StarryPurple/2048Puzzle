#include "include/game_logic.h"

namespace PZ2048 {

// You can add global variables here.
// If your IDE suggested some identifiers like "static", "inline" or "extern", you'd better learn about them
// and decide whether, how and where to use them.
// Or if you want to use type aliases, structures, classes or something else,
// just go ahead! You are free (and encouraged) to use them to make your code clearer and more integrated.
// Just don't modify the signatures of existing functions.

inline int rows, cols;

// You are free to add helper functions.

void Start(int row_num, int col_num, uint game_seed) {
  srand(game_seed); // Should be the PZ2048::srand(uint).
  rows = row_num;
  cols = col_num;

  // You may want to add more lines.
  /** implementation here **/
}

std::pair<int, int> EndGame() {
  /** implementation here **/
  return {0, 0};
}

int GetRows() { return rows; }

int GetCols() { return cols; }

bool TryRun(char dir) {
  /** implementation here **/
  return false;
}

bool Undo() {
  /** implementation here **/
  return false;
}

void SetTile(int row_index, int col_index, int value) {
  /** implementation here **/
}

int GetTile(int row_index, int col_index) {
  /** implementation here **/
  return 0;
}

int Score() {
  /** implementation here **/
  return 0;
}

int Steps() {
  /** implementation here **/
  return 0;
}

bool HasReachedTarget(int target) {
  /** implementation here **/
  return false;
}

bool Stuck() {
  /** implementation here **/
  return false;
}

void PrintBoard() {
  // The output format is fixed. Read server.h for description.
  /** implementation here **/
}

}