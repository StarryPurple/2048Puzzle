#include "include/utils.h"

#include <random>

namespace PZ2048 {

inline std::mt19937_64 gen;

void srand(uint seed) {
  gen.seed(seed);
}

uint rand() {
  return gen();
}



}