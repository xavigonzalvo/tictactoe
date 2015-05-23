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
// Generic state handler. List of all states that happen in an episode.

#ifndef TTT_ENVIRONMENT_STATE_HANDLER_H_
#define TTT_ENVIRONMENT_STATE_HANDLER_H_

#include <iostream>
#include <vector>

namespace ttt {

class StateHandler {
 public:
  virtual ~StateHandler() {}

  virtual const State *Get(int i) const = 0;
  virtual void Add(const State *state) = 0;
  virtual void Clear() = 0;

 protected:
  StateHandler() {}
};

template <class StateType>
class SpecializedStateHandler : public StateHandler {
 public:
  SpecializedStateHandler() {}
  ~SpecializedStateHandler() {}

  const State *Get(int i) const {
    if (i >= states_.size()) {
      std::cerr << "Index out of bounds, id: " << i << " size: "
           << states_.size();
    }
    return static_cast<const State *>(&states_[i]);
  }
  void Add(const State *state) {
    const StateType *state_type = dynamic_cast<const StateType *>(state);
    states_.push_back(*state_type);
  }
  void Clear() { states_.clear(); }

 private:
  std::vector<StateType> states_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_STATE_HANDLER_H_
