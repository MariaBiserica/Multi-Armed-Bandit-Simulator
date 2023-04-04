# Multi-Armed-Bandit-Simulator
Addressed topic: Online algorithms -> Multi-armed bandit problem

What are online algorithms? Online algorithms represent a theoretical substructure for studying problems in interactive computing. They model, in particular, that the input in an interactive system doesn’t arrive as a batch but as a sequence of input portions and that the system must react in response to every incoming portion. Furthermore, they take into account the fact that future input is unpredictable at any given time.

Background: 

In 1952 Robbins introduced the multi-armed bandit problem and it has sparked a lot of interest in machine learning applications since then. The name for the model comes from the one-armed bandit. This is a familiar name for a slot machine. The problem highlights a situation where a gambler walks into a casino and sits down at a row of slot machines. Each one produces a random payout according to some distribution. This result is unknown to the gambler. Because the distributions are unknown, the gambler must experiment to learn about them. The gambler faces an inherent tradeoff as he begins to pull arms and receive payouts.

Scope: 

The choice of the multi-arm bandit problem is motivated by its application to machine learning as a way to effectively measure the performance of learning algorithms. Our paper strengthens the results of the previous papers. It aims to present the optimal choice of the learning algorithm based on a Gaussian or Bernoulli distribution, with a practical and easy-to-understand implementation of the algorithm.

Methods: 

In the age of speed, all applications are built on the principle of fast learning, but because of this sometimes the long-term optimal performance is overlooked. We examine short-term (200 iterations) and long-term (1000 iterations) behaviors of several popular Multi-Arm Bandit solutions, for Gaussian and Bernoulli distributions, such as: Epsilon-Greedy, Boltzmann, Upper-Confidence-Bound and Gradient Bandit with softmax action preference.
