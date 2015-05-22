# A learning configuration where Q-learning plays against a random agent.

alpha: 0.2
gamma: 0.95
epsilon: 0.1
agents {
  learner: "QLearningAgent"
  opponent: "RandomAgent"
}
