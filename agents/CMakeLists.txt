# Agent functionality.

add_library(agent STATIC base_agent.cc human_agent.cc qlearning_agent.cc
  random_agent.cc sarsa_agent.cc)
