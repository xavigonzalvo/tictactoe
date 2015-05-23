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
// A generic state handler. Inherit from this class to define your own world.
// You'll need to define:
//   - valid
//   - Do
//   - ToString
//   - DebugString
// And optionally:
//   - Init

#ifndef TTT_ENVIRONMENT_STATE_H_
#define TTT_ENVIRONMENT_STATE_H_

#include <string>

namespace ttt {

class State {
 public:
  virtual ~State() {}

  virtual bool Init() {
    finished_ = false;
    num_actions_ = 0;
    id_ = 0;
    return true;
  }

  // Returns true if the action is valid.
  virtual bool Valid(int action) const = 0;

  // Executes and actions and returns false if there's an error. It
  // also returns a reward.
  virtual bool Do(int action, bool opponent, float *reward) = 0;

  // To be used as a key.
  virtual std::string ToString() const = 0;

  // For visualization purposes.
  virtual std::string DebugString() const = 0;

  // Returns true if it's the final state.
  virtual bool finished() const { return finished_; }

  // Id handlers.
  int id() const { return id_; }
  void NextId() { ++id_; }

 protected:
  explicit State(int dimension)
      : id_(0), dimension_(dimension), num_actions_(0), finished_(false) {}

  // State id for reference.
  int id_;

  // Dimension of the state (eg. for a tictactoe 3x3 table, this would be 9).
  int dimension_;

  // A counter to control the number of total actions taken.
  int num_actions_;

  // True if the state is in final position.
  bool finished_;
};

}  // namespace ttt

#endif  // TTT_ENVIRONMENT_STATE_H_
