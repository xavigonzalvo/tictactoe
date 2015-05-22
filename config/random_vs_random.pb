# A learning configuration where Sarsa plays against itself.

alpha: 0.8
gamma: 0.9
epsilon: 0.1
agents {
  learner: "RandomAgent"
  opponent: "RandomAgent"
}
