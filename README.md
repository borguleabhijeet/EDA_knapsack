# EDA_knapsack
This report we present about estimation of distribution of algorithms.
![alt text](https://github.com/borguleabhijeet/EDA_knapsack/blob/master/EDA_knapsack/works.jpg)
Algorithm 
1. Initialize population:
A. We generate 0-1 chromosomes. The individual length is 500
B. The population size 100
2. Check the Fitness:
A. We check the fitness of the population
3. Sort the population:
A. We sort the population based on fitness values
4. Truncate selection:
A. We use the 0.5 (first half) of the population to compute the probability
vector
5. Create probability vector:
A. The best population then evaluated by summing up occurrence of ones and
dividing the total size which forms probability vector.
B. After computing a probability vector, we sampled it by comparing with
random probability to form the new population.
6. Check fitness:
A. We check the fitness of the population and then continued using the higher
fitness population without exceeding the weight limit.
