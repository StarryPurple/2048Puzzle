#ifndef PUZZLE_2048_UTILS_HPP
#define PUZZLE_2048_UTILS_HPP

#include <utility>

using uint = unsigned int;

namespace PZ2048 {

// reset the generator with a seed.
// fixed seed gives a fixed rand.
// if input seed = 0, use system clock to summon a random(adj.) random(n.) seed.
void srand(uint seed);

// give a random uint.
uint rand();

// give the last seed set in srand().
uint get_seed();

}

#endif // PUZZLE_2048_UTILS_HPP
