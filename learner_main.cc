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
// Main tool to train an agent to play tic-tac-toe using reinforcement
// learning. Use config.proto to set the options.

#include <fcntl.h>
#include <fstream>
#include <memory>
#include <string>

#include <gflags/gflags.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

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
DEFINE_bool(verbose, false,
            "If true, intermediate rewards are printed");

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
    std::cout << "Percetange of won games: "
         << static_cast<float>(num_wins) / FLAGS_epochs << std::endl;;
    std::cout << "Percetange of draw games: "
         << static_cast<float>(num_draw) / FLAGS_epochs << std::endl;;
    std::cout << "Percetange of lost games: "
         << static_cast<float>(num_lost) / FLAGS_epochs << std::endl;;
  }

  int num_lost;
  int num_draw;
  int num_wins;
};

bool Run() {
  Config config;
  int fp = open(FLAGS_config_path.c_str(), O_RDONLY);
  if (fp < 0) {
    std::cerr << "Error opening the config file: " << FLAGS_config_path
              << std::endl;
    return false;
  }
  google::protobuf::io::FileInputStream fileInput(fp);
  fileInput.SetCloseOnDelete(true);
  if (!google::protobuf::TextFormat::Parse(&fileInput, &config)) {
    std::cerr << "Failed to parse config" << std::endl;
    return false;
  }

  // Initialize actions.
  Actions actions;
  InitTicTacToeActions(&actions, TicTacToeEnvironment::kTableDimension);

  // Initialize state handler.
  SpecializedStateHandler<TicTacToeState> state_handler;

  // Create agents.
  BaseAgent *learner_agent =
      AgentFactory(config.agents().learner(), config, actions, state_handler);
  if (!FLAGS_load_learner_agent_model_path.empty()) {
    if (!learner_agent->Load(FLAGS_load_learner_agent_model_path)) {
      return false;
    }
  }
  BaseAgent *opponent_agent =
      AgentFactory(config.agents().opponent(), config, actions, state_handler);
  if (!FLAGS_load_opponent_agent_model_path.empty()) {
    if (!opponent_agent->Load(FLAGS_load_opponent_agent_model_path)) {
      return false;
    }
  }

  // Initialize environment.
  TicTacToeEnvironment environment(opponent_agent, &state_handler);

  // For each epoch, run an episode until it's finished.
  SimpleStats stats;
  for (int epoch = 0; epoch < FLAGS_epochs; ++epoch) {
    if (!environment.Start(FLAGS_verbose)) {
      std::cerr << "Failed to start environment";
      return false;
    }
    // TODO(xavigonzalvo): randomize the first player?
    learner_agent->SetAction(environment.state());
    if (FLAGS_verbose) std::cout << "Epoch " << epoch << std::endl;
    while (!environment.end_of_episode()) {
      if (!environment.Run(learner_agent->action())) {
        std::cerr << "Failed to run environment on epoch " << epoch;
        return false;
      }
      if (!environment.end_of_episode()) {
        learner_agent->SetNextAction(environment.state());
      }
      if (!learner_agent->Update(environment.reward(),
                                 environment.end_of_episode())) {
        std::cerr << "Failed to update learner" << std::endl;
        return false;
      }
      if (FLAGS_verbose) {
        std::cout << "  Reward = " << environment.reward() << std::endl;
      }
    }
    if (opponent_agent->human()) {
      std::cout << "Final table: " << environment.state()->DebugString()
                << std::endl << "--------------" << std::endl;
    }
    stats.Update(environment.reward());
  }

  // Some simple stats.
  stats.Finalize();

  // Save learned model.
  if (!FLAGS_save_agent_model_path.empty()) {
    std::cout << "Number of states: " << learner_agent->NumStates()
              << std::endl;
    if (!learner_agent->Save(FLAGS_save_agent_model_path)) {
      std::cerr << "Failed to save learner data";
      return false;
    }
  }
  return true;
}

}  // namespace
}  // namespace ttt

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  return ttt::Run() ? 0 : 1;
}
