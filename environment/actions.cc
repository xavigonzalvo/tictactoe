#include "environment/actions.h"

namespace ttt {

int Actions::size() const {
  return size_;
}

int Actions::Random(const State *state) const {
  int action = random_.Uniform(size_);
  while (!state->Valid(action)) {
    action = random_.Uniform(size_);
  }
  return action;
}

// Adds a new action and returns its integer id.
int Actions::Add() {
  return size_++;
}

}  // namespace ttt
