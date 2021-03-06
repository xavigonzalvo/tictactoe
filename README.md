Tic-Tac-Toe learning with Reinforcement learning (RL)
======================================================

[![Build Status](https://travis-ci.org/xavigonzalvo/tictactoe.svg)](https://travis-ci.org/xavigonzalvo/tictactoe)

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

Installation
------------

- Install protocol buffers from [Google developers' page](https://developers.google.com/protocol-buffers/)

- Install gflags from [http://gflags.github.io/gflags/#download](http://gflags.github.io/gflags/#download)

- Compile from source:

        $ mkdir build && cd build
        $ cmake ..
        $ make


Configuration
-------------

You can use the configutation defined in ```config.proto```. For example, to
define two Sarsa agents that interact with themselves, use the
following:

    alpha: 0.8
    gamma: 0.9
    epsilon: 0.1
    agents {
      learner: "SarsaAgent"
      opponent: "SarsaAgent"
    }

You will find more configurations in the ```config/``` folder.

The rest of the variables are the typical important factors used in RL
(eg. learning rate, discount factor). Please refer to config.proto for
more information.

Learning
--------

Use it like this:

    ./learner --config_path ../config/sarsa_vs_sarsa.pb --epochs 1000000

This will train a Sarsa agent while interacting with itself. In order
to save the final models, add the following options:

    --save_agent_model_path /tmp/sarsa.model


Human agent
-----------

You can interact directly with the system specifying a human agent:

    ./learner --config_path ../config/human_vs_sarsa.pb \
      --epochs 10 --load_learner_agent_model_path ../models/random_vs_sarsa_epochs2000000.model


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
