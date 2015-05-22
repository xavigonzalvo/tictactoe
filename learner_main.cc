// Main tool to train an agent to play tic-tac-toe using reinforcement
// learning. Use config.proto to set the options.

#include <fstream>
#include <memory>
#include <string>

#include <gflags/gflags.h>
#include "agents/agent_factory.h"
#include "agents/base_agent.h"
#include "environment/state_handler.h"
#include "environment/tictactoe_actions.h"
#include "environment/tictactoe_environment.h"
#include "config.pb.h"

DEFINE_string(config_path, "",
              "Path to the text config proto");
DEFINE_int32(epochs, 1000,
             "Number of epochs to train");
DEFINE_string(save_agent_model_path, "",
              "Path to save the model of the agent");
DEFINE_string(load_learner_agent_model_path, "",
              "Path to load the model of the learner agent");
DEFINE_string(load_opponent_agent_model_path, "",
              "Path to load the model of the opponent agent");

namespace ttt {
namespace {

struct SimpleStats {
 public:
  SimpleStats() : num_lost(0), num_draw(0), num_wins(0) {}

  void Update(float reward) {
    if (reward == TicTacToeState::kSuccessReward) {
      num_wins++;
    }
    if (reward == TicTacToeState::kFailureReward) {
      num_lost++;
    }
    if (reward == TicTacToeState::kInGameReward) {
      num_draw++;
    }
  }

  void Finalize() const {
    cout << "Percetange of won games: "
         << static_cast<float>(num_wins) / FLAGS_epochs << endl;;
    cout << "Percetange of draw games: "
         << static_cast<float>(num_draw) / FLAGS_epochs << endl;;
    cout << "Percetange of lost games: "
         << static_cast<float>(num_lost) / FLAGS_epochs << endl;;
  }

  int num_lost;
  int num_draw;
  int num_wins;
};

bool Run() {
  Config config;
  fstream input(FLAGS_config_path.c_str(), ios::in | ios::binary);
  if (!config.ParseFromIstream(&input)) {
    cerr << "Failed to parse config" << endl;
    return false;
  }

  // Initialize actions.
  Actions actions;
  InitTicTacToeActions(&actions, TicTacToeEnvironment::kTableDimension);

  // Initialize state handler.
  SpecializedStateHandler<TicTacToeState> state_handler;

  // Create agents.
  std::unique_ptr<BaseAgent> learner_agent(
      AgentFactory(config.agents().learner(), config, actions, state_handler));
  if (!FLAGS_load_learner_agent_model_path.empty()) {
    if (!learner_agent->Load(FLAGS_load_learner_agent_model_path)) {
      return false;
    }
  }
  std::unique_ptr<BaseAgent> opponent_agent(
      AgentFactory(config.agents().opponent(), config, actions, state_handler));
  if (!FLAGS_load_opponent_agent_model_path.empty()) {
    if (!opponent_agent->Load(FLAGS_load_opponent_agent_model_path)) {
      return false;
    }
  }

  // Initialize environment.
  TicTacToeEnvironment environment(opponent_agent.get(), &state_handler);

  // For each epoch, run an episode until it's finished.
  SimpleStats stats;
  for (int epoch = 0; epoch < FLAGS_epochs; ++epoch) {
    if (!environment.Start()) {
      cerr << "Failed to start environment";
      return false;
    }
    // TODO(xavigonzalvo): randomize the first player?
    learner_agent->SetAction(environment.state());
    cout << "Epoch " << epoch;
    while (!environment.end_of_episode()) {
      if (!environment.Run(learner_agent->action())) {
        cerr << "Failed to run environment on epoch " << epoch;
        return false;
      }
      if (!environment.end_of_episode()) {
        learner_agent->SetNextAction(environment.state());
      }
      if (!learner_agent->Update(environment.reward(),
                                 environment.end_of_episode())) {
        cerr << "Failed to update learner";
        return false;
      }
      cout << "  Reward = " << environment.reward();
    }
    if (opponent_agent->human()) {
      cout << "Final table: " << environment.state()->DebugString()
           << endl << "--------------" << endl;
    }
    stats.Update(environment.reward());
  }

  // Some simple stats.
  stats.Finalize();

  // Save learned model.
  if (!FLAGS_save_agent_model_path.empty()) {
    cout << "Number of states: " << learner_agent->NumStates() << endl;
    if (!learner_agent->Save(FLAGS_save_agent_model_path)) {
      cerr << "Failed to save learner data";
      return false;
    }
  }
  return true;
}

}  // namespace
}  // namespace ttt

int main(int argc, char **argv) {
  InitGoogle(argv[0], &argc, &argv, true);
  ttt::Run() ? return 0 : return 1;
}
