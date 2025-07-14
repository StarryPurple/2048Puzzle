#ifndef PUZZLE_2048_UTILS_HPP
#define PUZZLE_2048_UTILS_HPP

#include <utility>

using uint = unsigned int;

namespace PZ2048 {

// reset the generator with a seed.
// fixed seed gives a fixed rand.
void srand(uint seed);

// give a random uint.
uint rand();

}

#endif // PUZZLE_2048_UTILS_HPP
