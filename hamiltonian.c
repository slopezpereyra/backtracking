#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"
#include <stdbool.h>

typedef list vertex;

//graph subGraph(graph g, int vertex){
//    graph sub_graph = createGraph(g -> V - 1);
//    for (int i = 0; i < g; )
//}
//


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

bool can_be_solved(graph g, int start){

    node neighbors = (g -> adj_l)[start];
    for (node neigh = neighbors; neigh != NULL; neigh = neigh -> next){
        if ((g -> adj_l)[neigh -> value] == NULL){
            continue;
        }if (list_has((g -> adj_l)[neigh -> value], 0)){
            return(true);
        }
    }

    return(false);
}

int hamiltonian_cycle(graph g, int start){
    printf("\n---------------------------------------------------------\n");
    printGraph(g);
    list candidates = (g -> adj_l)[start];
//    if (!can_be_solved(g, start)){
//        printf("Cannot be solved; returning inf... \n");
//        return(1000000);
//    }

    if (are_all_null(g, start)){
        printf("******************* NULL EVEN ***************\n");
        if (list_has((g -> adj_l)[start], 0)){
            return(1);
        }else{
            printf("Ret inf\n");
            return(1000000);
        }
    }
    int n = llength(candidates);
    int solutions[n];
    int i = 0;
    for (node v = candidates; v != NULL; v = v -> next){
        if ((g -> adj_l)[v -> value] == NULL){
            continue;
        }
        printf("Taking path %d -> %d\n", start, v -> value);
        graph subgraph = cloneGraphWithoutNode(g, start);
        solutions[i] = 1 + hamiltonian_cycle(subgraph, v -> value);
        i = i+1;
    }    
    return(findMinimum(solutions, n));
}



// Driver code
int main() {
    int V = 5;
    graph g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 4);
    printGraph(g);
    int sol = hamiltonian_cycle(g, 0);
    printf("Solution is %d\n", sol);
}


