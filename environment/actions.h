/*
The MIT License (MIT)

Copyright (c) <year> <copyright holders>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
// Main action handler. This class is generic so no further definitions should
// be required. Have a look at tictactoe_actions.h to see and example.
//
// Usage:
//    Actions actions;
//    for (int i = 0; i < ACTIONS; ++i)
//      actions.Add();

#ifndef TTT_ENVIRONMENT_ACTIONS_H_
#define TTT_ENVIRONMENT_ACTIONS_H_

#include <vector>

#include "core/simple_random.h"
#include "environment/state.h"

namespace ttt {

class Actions {
 public:
  Actions() : size_(0), random_() {}
  ~Actions() {}

  // Returns the number of actions.
  int size() const;

  // Returns a random action.
  int Random(const State *state) const;

  // Adds a new action and returns its integer id.
  int Add();

 private:
  // Number of actions.
  int size_;

  // Random number generator for the random action selection in
  // exploratory mode.
  mutable SimpleRandom random_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_ACTIONS_H_
