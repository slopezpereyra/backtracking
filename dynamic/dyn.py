import numpy as np
import random

# Binomial coefficient 

# Recall that C(n, k) = C(n - 1, k - 1) + C(n - 1, k)
# with C(n, 0) = 1

def bc(n, k, show_table_fill=False):
  
    C = [[0 for x in range(k+1)] for x in range(n + 1)]
    for i in range(n + 1):
        for j in range(k + 1):
            if j == 0 or j == i:
                C[i][j] = 1
            else:
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j]
            if show_table_fill:
                print("({}, {}) :\n {}\n".format(i, j, np.matrix(C)))
    
    return C[n][k]

# Minimum number of coins needed to pay a certain sum.
def coin_change(total, denoms, show_table_fill=False):

    denom_count = len(denoms)
    C = [[0 for x in range(total + 1)] for x in range(denom_count + 1)]

    for i in range(denom_count + 1):
        for j in range(total + 1):
            if j == 0:
                C[i][j] = 0
            elif i == 0:
                C[i][j] = np.inf
            elif denoms[i - 1] > j:
                C[i][j] = C[i - 1][j]
            else:
                C[i][j] = min( C[i][j - denoms[i - 1]] + 1, C[i - 1][j] )

            if show_table_fill:
                print("({}, {}) :\n {}\n".format(i, j, np.matrix(C)))

    return(C[denom_count][total])
    
def knapsack_rec(capacity, values, weights, i):
    
    if (capacity <= 0):
        return(0)
    if i < 0:
        return np.NINF

    if weights[i] > capacity:
        return knapsack_rec(capacity, values, weights, i - 1)
    
    return max( knapsack_rec(capacity - weights[i], values, weights, i - 1) + values[i],
                knapsack_rec(capacity, values, weights, i - 1))
    
def knapsack(capacity, values, weights, show_table_fill=False):

    obj_count = len(values)
    C = [[0 for x in range(capacity + 1)] for x in range(obj_count + 1)]

    for i in range(obj_count + 1):
        for j in range(capacity + 1):
            if i == 0 or j == 0:
                C[i][j] = 0             # Base cases
            elif weights[i - 1] > j:
                C[i][j] = C[i - 1][j]
            else:
                C[i][j] = max( C[i-1][j], values[i - 1] + C[i - 1][j - weights[i - 1]] )
                
            if show_table_fill:
                print("({}, {}) :\n {}\n".format(i, j, np.matrix(C)))

    return(C[obj_count][capacity])


# Find the combination of k out of n measures that maximizes score 
# while ensuring that their total cost does not surpass C.
# Each measure has a profit of m₁, …, mₙ and a cost of d₁, …, dₙ. 
# The score of the ith measure is defind as mᵢ/dᵢ.

K = 9
def max_gain_bounded_cost_rec(M, D, C, k, i):

    if i < 0 or C <= 0 or k == K:
        return(0)

    if D[i] > C:
        return max_gain_bounded_cost_rec(M, D, C, k, i - 1)

    return max(
            max_gain_bounded_cost_rec(M, D, C, k, i - 1),
            max_gain_bounded_cost_rec(M, D, C - D[i], k + 1, i - 1) + M[i]/D[i]
            )


def max_gain_bounded_cost(M, D, C, K):

    n = len(M)
    R = [[[0 for _ in range(K + 1)] for _ in range(C + 1)] for _ in range(n + 1)]

    for i in range(n + 1):
        for j in range(C + 1):
            for q in range(K + 1):
                if i == 0 or j <= 0 or K == 0:
                    R[i][j][q] = 0
                elif D[i - 1] > j:
                    R[i][j][q] = R[i - 1][j][q]
                else:
                    R[i][j][q] = max( 
                                     R[i-1][j][q], 
                                     M[i-1]/D[i-1] + R[i-1][j - D[i-1]][q - 1]
                                     )

    return(R[n][C][K])


BOARD = [[random.randint(-3, 9) for _ in range(9)] for _ in range(9)]
print(np.matrix(BOARD))
def traveller_rec(i, j, s):

    if i > 8 or j > 8:
        return(0)

    if s < 0 or j < 0:
        return(np.NINF)

    return max(
            BOARD[i][j] + traveller_rec(i + 1, j, s + BOARD[i][j]),
            BOARD[i][j] + traveller_rec(i + 1, j + 1, s + BOARD[i][j]),
            BOARD[i][j] + traveller_rec(i + 1, j - 1, s + BOARD[i][j])
            )

# Assume a matrix A of 9×9 dimensions. 
#
#               {   0                                       i > 9
#  f(i, j, s) = { -∞                                        s < 0 ∨ j < 0
#               {  max ( Aᵢⱼ + f(i + 1, j, s + Aᵢⱼ),
#               {        Aᵢⱼ + f(i + 1, j + 1, s + Aᵢⱼ)     otherwise
#               {        Aᵢⱼ + f(i + 1, j - 1, s + Aᵢⱼ) 
#       

def traveller():
   
    C = [[0 for _ in range(10)] for _ in range(10)]






print(traveller_rec(0, 2, 0))


#print(max_gain_bounded_cost_rec([5, 10, 15, 20], [6, 7, 1, 9], 200, 0, 3))
#print(max_gain_bounded_cost([5, 10, 15, 20], [6, 7, 1, 9], 200, 9))




#print(knapsack_rec(capacity = 50, values=[60, 100, 120], weights=[10, 20, 30], i=2))
#print(knapsack(capacity = 10, values=[60, 100, 120], weights=[1, 2, 3], show_table_fill=True))
