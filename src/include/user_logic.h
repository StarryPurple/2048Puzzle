#ifndef PUZZLE_2048_USER_LOGIC_H
#define PUZZLE_2048_USER_LOGIC_H

namespace PZ2048 {

// Don't try to use extern variables from server.cpp.

/**
 * Inform the client with the board params of the game.
 */
void Initialize(int row_num, int col_num);

/**
 * Read in the current board from stdin.
 * The data format is the same with your PrintBoard() in server.h.
 */
void ReadBoard();

// Dir Decide();

/**
 * Using the board status you've read with ReadBoard(), decide your next move.
 * @return a character among 'w', 's', 'a' and 'd'.
 */
char Decide();

}

#endif // PUZZLE_2048_USER_LOGIC_H