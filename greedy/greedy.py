import numpy as np 



def knapsack(weights, values, W):

    space_left = W 
    total_value = 0
    while (space_left > 0 and len(weights) > 0):
        index = select_knapsack(weights, values)
        if weights[index] <= space_left:
            fraction = 1
            space_left -= weights[index]
            total_value += values[index]
        else:
            fraction = space_left/weights[index]
            space_left = 0
            total_value += values[index]*fraction
        print("Choosing {} times object {} with {} and {}\nSpace left: {}\n Value {}\n".format(fraction, 
                                                                  index, 
                                                                  weights, 
                                                                  values, 
                                                                                  space_left,
                                                                                               total_value))
        del weights[index] 
        del values[index]

    return(total_value)

def select_knapsack(weights, values):

    max_rel_value = 0
    index = 0
    for i in range(len(weights)):
        if values[i]/weights[i] > max_rel_value:
            max_rel_value = values[i]/weights[i]
            index = i

    return index


def portions(expiracies, n):

    m = len(expiracies)
    if (n >= m): 
        return 0

    solution = []

    for i in range(n):
        index = find_min_index(expiracies)
        del expiracies[index]
        solution.append(index)

    return solution

def find_min_index(l):

    m = l[0]
    i = 0
    for j in range(1, len(l)):
        if l[j] <= m:
            m = l[j]
            i = j 

    return(i)

#print(knapsack([6, 5, 4], [12, 11, 8], 10))
print(portions([5, 2, 6, 6, 10], 3))

