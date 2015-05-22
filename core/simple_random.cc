#include "simple_random.h"

#include <stdlib.h>
#include <time.h>

namespace ttt {

SimpleRandom::SimpleRandom() {
  srand(time(NULL));
}

int SimpleRandom::Uniform(int size) const {
  return rand() % size;
}

float SimpleRandom::RndFloat() const {
  const float rnd = static_cast<float>(rand());
  return rnd / static_cast<float>(RAND_MAX);
}

}  // namespace ttt
