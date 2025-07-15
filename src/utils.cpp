#include "include/utils.h"

#include <random>
#include <chrono>

namespace PZ2048 {

static std::mt19937_64 gen;
static uint gen_seed;

void srand(uint seed) {
  if(seed == 0) {
    seed = static_cast<uint>(std::chrono::system_clock::now().time_since_epoch().count());
  }
  gen_seed = seed;
  gen.seed(seed);
}

uint rand() {
  return gen();
}

uint get_seed() {
  return gen_seed;
}

}