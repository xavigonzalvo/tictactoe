// A generic state handler. Inherit from this class to define your own world.
// You'll need to define:
//   - valid
//   - Do
//   - ToString
//   - DebugString
// And optionally:
//   - Init

#ifndef EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_STATE_H_
#define EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_STATE_H_

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
  virtual string ToString() const = 0;

  // For visualization purposes.
  virtual string DebugString() const = 0;

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

#endif  // EXPERIMENTAL_USERS_XAVIGONZALVO_TTT_ENVIRONMENT_STATE_H_
