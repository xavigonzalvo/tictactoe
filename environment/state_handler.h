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
