#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


struct _graph {
    int V;
    list *adj_l; // pointer to a list (which is a pointer to _node).
};

typedef struct _graph * graph;

graph createGraph(int n);

void addEdge(graph g, int src, int dest);

void removedge(graph g, int src, int dest);

void printGraph(graph g);

node createNewNode(int value);

node getNode(graph g, int i);

graph cloneGraphWithoutNode(graph original, int removeIndex);

bool pathExists(graph g, int from, int to, bool hamiltonian);
bool hamPathExists(graph g, int from, int to);

int countTraversedNodes(graph g);

void destroyGraph(graph g);
