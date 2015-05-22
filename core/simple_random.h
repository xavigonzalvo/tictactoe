#ifndef TTT_CORE_SIMPLE_RANDOM_H_
#define TTT_CORE_SIMPLE_RANDOM_H_

namespace ttt {

class SimpleRandom {
 public:
  SimpleRandom();

  // Generates a uniformly distributed random number between [0,size].
  int Uniform(int size) const;

  float RndFloat() const;
};

}  // namespace ttt

#endif  // TTT_CORE_SIMPLE_RANDOM_H_
