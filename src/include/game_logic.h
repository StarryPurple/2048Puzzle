#ifndef PUZZLE_2048_GAME_LOGIC_H
#define PUZZLE_2048_GAME_LOGIC_H

#include <string>
#include <vector>

#include "utils.h"

namespace PZ2048 {

/**
 * Initialize and start a Puzzle2048 game.
 */
void Start(int row_num, int col_num, int target = 2048, uint game_seed = 0);

/**
 * End the game.
 *
 * @return the steps taken and the score accumulated so far.
 */
std::pair<int, int> EndGame();

/**
 * @return number of board rows.
 */
int GetRows();

/**
 * @return number of board columns.
 */
int GetCols();

// I've thought of using enum classes, but maybe it's a bit too fast for you.
// enum class Dir { Invalid, Left, Right, Up, Down };
// bool TryRun(Dir dir);

/**
 * Try to take a step with the given direction.
 * @param dir A valid dir is one of 'w', 's', 'a' and 'd', intends to swipe tiles up, down, left or right.
 * @return whether the operation succeeds.
 *
 * Invalid inputs shall be considered as doing nothing. You should do nothing and return false.
 *
 * If operation succeeds, change the status of your gaming board.
 */
bool TryRun(char dir);

/**
 * Try to undo an operation.
 * Succeeds only when it has a previous move, and it is not an undo.
 * The board status, the score and the steps count should all be undone.
 *
 * @return whether this undo succeeds.
 */
bool Undo();

/**
 * Set a tile to a given value.
 * Should only be called in GenerateTile() (or testers).
 *
 * The given row index and column index is 0-based.
 */
void SetTile(int row_index, int col_index, int value);

/**
 * Get the value of given tile. Empty tile slot should be considered holding value 0.
 *
 * The given row index and column index is 0-based.
 */
int GetTile(int row_index, int col_index);

/**
 * @return the score the player had got.
 *
 * The score starts from 0 at the beginning of a game (the call of Startup(...) function).
 * Every time two tiles valued N are combined into a new tile valued 2N, the score should be increased by 2N.
 */
int Score();

/**
 * @return the valid steps the player had taken.
 *
 * The counter starts from 0 at the beginning of a game (the call of Startup(...) function).
 * Every time a valid operation (some tiles moved and combined) is taken, the counter should be increased by 1.
 */
int Steps();

/**
 *
 * @return The target set before this game.
 */
int GetTarget();

/**
 * @return whether the largest number on the board reaches the given value.
 */
bool HasReachedTarget();

/**
 * @return whether no valid operation can be performed.
 */
bool Stuck();

/**
 * Print the status of the board into stdout.
 *
 * You should output #row_number lines. Each of them should contain #column_number numbers.
 * You'll need #row_number endlines (std::endl or '\n').
 *
 * Empty tile slots should be considered as holding value 0.
 * Every tile value should be considered as a 4-digit number (same as 2048), aligned to the left, padded with spaces.
 *
 * For example: (0 for empty tiles, '>' signals the beginning of a line)
 *
 * >0    2    2    16  (\n here)
 * >2    4    16   4   (\n here)
 * >1024 8    0    4   (\n here)
 * >0    256  128  2   (\n here)
 * >
 * or:
 * >0    2    2    16(\n here)
 * >2    4    16   4(\n here)
 * >1024 8    0    4(\n here)
 * >0    256  128  2(\n here)
 * >
 * (Since unseeable spaces are filtered, reserving them is optional.)
 *
 *
 * Hint: std::setw(int), std::left
 */
void PrintBoard();

/*
 * Discarded design.
 *
 * Try to redo an operation.
 *
 * Succeeds only when it has a previous move, and it is an undo.
 *
 * @return whether this redo succeeds.
bool Redo();
*/

// Actually the following functions should also be written in server.cpp.
// But for banning you from overwriting, we choose to define here.

inline uint GetCurrentSeed() {
  return get_seed();
}

/**
 * This function is designed for debugging and testing.
 * You shall use this function in your other codes.
 * You can modify it locally, but remember the function in online judger will stick to the original version.
 *
 * Randomly generate a tile according to the board.
 * If board is full, returns {{-1, -1}, -1}.
 * Otherwise, set the tile to that value and returns the tile position and the value.
 *
 * pos: randomly chose from empty slots.
 * value: 90% for 2, 10% for 4.
 */
inline std::pair<std::pair<int, int>, int> TryGenerateTile() {
  std::vector<std::pair<int, int>> slot_list;
  int row_num = GetRows(), col_num = GetCols();
  for(int i = 0; i < row_num; i++)
    for(int j = 0; j < col_num; j++)
      if(GetTile(i, j) == 0)
        slot_list.emplace_back(i, j);
  if(slot_list.empty())
    return {{-1, -1}, -1};
  auto pos = rand(), sig = rand();
  pos %= slot_list.size();
  int row = slot_list[pos].first, col = slot_list[pos].second;
  sig %= 10;
  int val = (sig == 0 ? 4 : 2);
  SetTile(row, col, val);
  return {{row, col}, val};
}

/**
 * @return The identity string of the board status.
 */
inline std::string SerializeBoard() {
  int row_num = GetRows(), col_num = GetCols();
  std::string res;
  for(int i = 0; i < row_num; i++) {
    for(int j = 0; j < col_num; j++) {
      res += std::to_string(GetTile(i, j));
      if(j != col_num - 1) res += ' ';
    }
    if(i != row_num - 1) res += '\n';
  }
  return res;
}
}

#endif // PUZZLE_2048_GAME_LOGIC_H