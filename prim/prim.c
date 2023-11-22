#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"
#include <stdbool.h>
#include <time.h>


/*
 * Finds shortest generating tree
 */




// Example code
int main() {
    int V = 6;
    graph g = createGraph(V);
    addEdge(g, 0, 1);
    addEdge(g, 0, 4);
    addEdge(g, 0, 3);
    addEdge(g, 1, 2);
    addEdge(g, 1, 5);
    addEdge(g, 2, 3);
    addEdge(g, 1, 5);
    addEdge(g, 5, 2);
    addEdge(g, 3, 4);
    clock_t start_time, end_time;
    start_time = clock(); // Record the start time
    double cpu_time_used;
    int sol = hamCycle(g);
    printf("\n");
    printf("Solution is %d\n", sol);
    end_time = clock(); // Record the end time
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
}

