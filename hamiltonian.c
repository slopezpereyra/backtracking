#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"
#include <stdbool.h>
#include <time.h>

int findMinimum(int arr[], size_t size) {
    if (size == 0) {
        // Handle the case of an empty array (no minimum).
        return 0; // You can choose a suitable default value or handle the error differently.
    }
    int min = arr[0]; // Assume the first element is the minimum.
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i]; // Update the minimum if a smaller value is found.
        }
    }
    return min;
}

bool are_all_null(graph g, int except){
    for(int i = 0; i < g -> V; i++){
        if (i == except){
            continue;
        }
        if((g -> adj_l)[i] != NULL){
            return(false);
        }
    }
    return(true);
}

bool can_be_solved(graph g, int current_node){
    node zero_node = (g -> adj_l)[0];

    for (int i = 1; i < g -> V; i++){
        if (i == current_node || (g -> adj_l)[i] == NULL){
            continue;
        }
        node vertex = get_ith_node(g, i);
        if (list_has(vertex, 0)){
            if (pathExists(g, current_node, i)){
                return(true);
            }
        }
    }
    return(false);
}


int hamiltonian_cycle(graph g, int start){
    
    if (are_all_null(g, start)){
        if (list_has((g -> adj_l)[start], 0)){
            return(1);
        }else{
            return(1000000);
        }
    }
    // This makes the algorithm a backtracking one.
    // Remove this caluse and the algorithm is greedy.
    if (!can_be_solved(g, start)){
        return(1000000);
    }
    
    list candidates = (g -> adj_l)[start];
    int n = llength(candidates);
    int solutions[n];
    int i = 0;
    for (node v = candidates; v != NULL; v = v -> next){
        if ((g -> adj_l)[v -> value] == NULL){
            continue;
        }
        graph subgraph = cloneGraphWithoutNode(g, start);
        solutions[i] = 1 + hamiltonian_cycle(subgraph, v -> value);
        i = i+1;
    }
    return(findMinimum(solutions, n));
}



// Driver code
int main() {
    int V = 6;
    graph g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
    addEdge(g, 1, 4);
    addEdge(g, 1, 5);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 4);
    addEdge(g, 4, 5);

    clock_t start_time, end_time;
    start_time = clock(); // Record the start time

    // Your algorithm or code to measure here = 0.000467
    //                                          0.00036

    double cpu_time_used;

    int sol = hamiltonian_cycle(g, 0);
    printf("Solution is %d\n", sol);
    end_time = clock(); // Record the end time
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
}
