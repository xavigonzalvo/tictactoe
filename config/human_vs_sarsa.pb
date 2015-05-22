# A learning configuration where Sarsa plays against a human agent.

alpha: 0.8
gamma: 0.9
epsilon: 0.0  # No exploration
agents {
  learner: "SarsaAgent"
  opponent: "HumanAgent"
}
