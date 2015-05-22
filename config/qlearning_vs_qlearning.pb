# A learning configuration where Sarsa plays against itself.

alpha: 0.2
gamma: 0.95
epsilon: 0.1
agents {
  learner: "QLearningAgent"
  opponent: "QLearningAgent"
}
