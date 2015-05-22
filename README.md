#Tic-Tac-Toe learning with Reinforcement learning (RL)
======================================================

This is a simple RL library to train a Tic-Tac-Toe game using
on-policy and off-policy algorithms. The RL learning code is fairly
generic and it includes two main directories following the definition
of RL, that is, agents interact with an environment executing actions
and receving a reward:

- "agents": where the learning is happening. You can inherit from the
  BaseAgent class and implement your own method.

- "environment": There are actions, states and an environment. Class
  State is an abstraction so that it is possible to define your own
  state definition that handles the so called world. Class Actions is
  generic by definition so all is needed is to add the required
  actions. Environment is also abstracted.

Supported learning agents are Sarsa and Q-learning.

Configuration
-------------

You can use the configutation defined in config.proto. For example, to
define two Sarsa agents that interact with themselves, use the
following:

  alpha: 0.8
  gamma: 0.9
  epsilon: 0.1
  agents {
    learner: "SarsaAgent"
    opponent: "SarsaAgent"
  }

You will find more configurations in the config/ folder.

The rest of the variables are the typical important factors used in RL
(eg. learning rate, discount factor). Please refer to config.proto for
more information.

Learning
--------

Simply compile the main tool:

blaze build -c opt experimental/users/xavigonzalvo/ttt:learner

and use it like this:

./blaze-bin/experimental/users/xavigonzalvo/ttt/learner --config_path experimental/users/xavigonzalvo/ttt/config/sarsa_vs_sarsa.pb --epochs 1000000

Alternatively you can just build a predefined training:

blaze build -c opt experimental/users/xavigonzalvo/ttt:train_random_vs_sarsa
less blaze-genfiles/experimental/users/xavigonzalvo/ttt/models/random_vs_sarsa.result

You can see possible trainable configurations by doing this:

blaze query experimental/users/xavigonzalvo/ttt/... | grep train_

Human agent
-----------

You can interact directly with the system specifying a human agent:

blaze build -c opt experimental/users/xavigonzalvo/ttt:learner
blaze-bin/experimental/users/xavigonzalvo/ttt/learner --config_path experimental/users/xavigonzalvo/ttt/config/human_vs_sarsa.pb \
  --epochs 10 --load_learner_agent_model_path experimental/users/xavigonzalvo/ttt/models/random_vs_sarsa_epochs2000000.model


TODO
====

In priority order:

- Randomize order of players.
- Save final reward.
- Save some proper stats.
- Add unit test for actions and agents.
- Transfer q-table between interacting agents (every 1000 games?)
- Reduce e-greedy probability as learning evolves (1/t?)
- Add eligibility traces.
