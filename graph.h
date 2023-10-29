#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct _graph {
    int V;
    node *adj_l; // pointer to a pointer to node
};

typedef struct _graph * graph;

graph createGraph(int n);

void addEdge(graph g, int src, int dest);

void removedge(graph g, int src, int dest);

void printGraph(graph g);

node createNewNode(int value);

node get_ith_node(graph g, int i);

graph cloneGraphWithoutNode(graph original, int removeIndex);

bool pathExists(graph g, int from, int to);
