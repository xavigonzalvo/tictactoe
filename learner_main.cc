// Main tool to train an agent to play tic-tac-toe using reinforcement
// learning. Use config.proto to set the options.

#include <memory>
#include <string>

#include "base/commandlineflags.h"
#include "base/init_google.h"
#include "base/logging.h"
#include "agents/base_agent.h"
#include "environment/state_handler.h"
#include "environment/tictactoe_actions.h"
#include "environment/tictactoe_environment.h"
#include "config.pb.h"
#include "file/base/file.h"
#include "file/base/helpers.h"

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

void Run() {
  Config config;
  QCHECK_OK(file::GetTextProto(FLAGS_config_path, &config, file::Defaults()));

  // Initialize actions.
  Actions actions;
  InitTicTacToeActions(&actions, TicTacToeEnvironment::kTableDimension);

  // Initialize state handler.
  SpecializedStateHandler<TicTacToeState> state_handler;

  // Create agents.
  CHECK(BaseAgentRegisterer::IsValid(config.agents().learner()));
  CHECK(BaseAgentRegisterer::IsValid(config.agents().opponent()));
  std::unique_ptr<BaseAgent> learner_agent(
      BaseAgentRegisterer::CreateByName(
          config.agents().learner(), config, actions, state_handler));
  if (!FLAGS_load_learner_agent_model_path.empty()) {
    QCHECK(learner_agent->Load(FLAGS_load_learner_agent_model_path));
  }
  std::unique_ptr<BaseAgent> opponent_agent(
      BaseAgentRegisterer::CreateByName(
          config.agents().opponent(), config, actions, state_handler));
  if (!FLAGS_load_opponent_agent_model_path.empty()) {
    QCHECK(opponent_agent->Load(FLAGS_load_opponent_agent_model_path));
  }

  // Initialize environment.
  TicTacToeEnvironment environment(opponent_agent.get(), &state_handler);

  // For each epoch, run an episode until it's finished.
  SimpleStats stats;
  for (int epoch = 0; epoch < FLAGS_epochs; ++epoch) {
    QCHECK(environment.Start());
    // TODO(xavigonzalvo): randomize the first player?
    learner_agent->SetAction(environment.state());
    VLOG(1) << "Epoch " << epoch;
    while (!environment.end_of_episode()) {
      CHECK(environment.Run(learner_agent->action()))
          << "Failed to run environment on epoch " << epoch;
      if (!environment.end_of_episode()) {
        learner_agent->SetNextAction(environment.state());
      }
      CHECK(learner_agent->Update(environment.reward(),
                                  environment.end_of_episode()));
      VLOG(1) << "  Reward = " << environment.reward();
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
    QCHECK(learner_agent->Save(FLAGS_save_agent_model_path));
  }
}

}  // namespace
}  // namespace ttt

int main(int argc, char **argv) {
  InitGoogle(argv[0], &argc, &argv, true);
  ttt::Run();
  return 0;
}
