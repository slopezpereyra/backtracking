#include <stdio.h> 
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>


/**
 * Allocates memory for new _node, sets its value to `value` and 
 * returns pointer to _node.
 */
node createNewNode(int value){
    node vertex = (node) malloc(sizeof(struct _node));
    vertex -> value = value;
    vertex -> next = NULL;
    return(vertex);
}

/**
*
* Creates and returns a graph (pointer to _graph).
*
* @description
*
* A _graph G is allocated. N nodes (pointer to _node) are allocated and the ith 
* node is stored as the ith element of the adjacency list of G. Thus, the 
* adjacency list of G is an array of nodes (pointers to _nodes).
*/
graph createGraph(int n){
    graph g = (graph) malloc(sizeof(struct _graph));
    g -> V = n;
    g -> adj_l = (struct _node**) malloc(n * sizeof(node));

    for (int i = 0; i < n; i++){
        (g -> adj_l)[i] = NULL;
    }
    return(g);
}

/*
 *
 * The `adj_l` of a graph is an array of pointers; each pointer points to a
 * list. Each lists corresponds to a vertex.
 *
 * This function adds `b` to the list of vertex `a`, and `a` to the list of
 * vertex `b` (undirected).
 *
 */
void addEdge(graph g, int a, int b){
    node new = createNewNode(b);
    (g -> adj_l)[a] = append((g -> adj_l)[a], new);
    new = createNewNode(a);
    (g -> adj_l)[b] = append((g -> adj_l)[b], new);
}

void removeEdge(graph g, int a, int b){
    (g -> adj_l)[a] = del((g -> adj_l)[a], b);
    (g -> adj_l)[b] = del((g -> adj_l)[b], a);
}


node getNode(graph g, int i){
    return( (g -> adj_l)[i] );
}

// Function to print the adjacency list
void printGraph(graph g) {
    for (int i = 0; i < g->V; i++) {
        node current = (g->adj_l)[i];
        printf("Adjacency list of vertex %d: ", i);
        while (current) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Recursive function that determines if path exists
// from node `from` to `to` with constraint of not walking
// through NULL nodes. May or may not impose hamiltonian constraint.
bool pathExists(graph g, int from, int to, bool hamiltonian){
    if (from == to){
        if (!hamiltonian) { return true; }
        return (countTraversedNodes(g) == ( g -> V ) - 1);
    } 
    if (getNode(g, to) == NULL) { return(false); }

    node node_from = getNode(g, from), node_to = getNode(g, to);
    bool exists = false;
    for (node vertex = node_to; vertex != NULL; vertex = vertex -> next){
        graph copy = cloneGraphWithoutNode(g, to);
        exists = exists || pathExists(copy, from, vertex -> value, hamiltonian);
        destroyGraph(copy); // clean memory from copy once it is done;
    }
    if (exists) {  printf("%d <-- ", to);}
    return(exists);
}

// 
int countTraversedNodes(graph g){
    int nulls = 0;
    for (int i = 0; i < g -> V; i++){
        if ((g -> adj_l)[i] == NULL ){
            nulls = nulls + 1;
        }
    }return(nulls);
}

graph cloneGraphWithoutNode(graph original, int removeIndex) {

    int n = original->V;
    graph newGraph = createGraph(n);

    for (int i = 0 ; i < original->V; i++) {
        if (i == removeIndex) {
            // Skip the removed vertex
            continue;
        }
        list original_node = (original -> adj_l)[i];
        if (original_node == NULL){
            continue;
        }
        node new_node = createNewNode(i);
        (newGraph -> adj_l)[i] = append( (newGraph -> adj_l)[i], new_node );
        *(newGraph -> adj_l)[i] = *original_node;
    }
    return newGraph;
}

void destroyGraph(graph g){

    for (int i = 0 ; i < g -> V; i++) {
         free( (g -> adj_l)[i] );
         (g -> adj_l)[i] = NULL;
    }
    free( g -> adj_l );
    ( g -> adj_l ) = NULL;
    free(g);
    g = NULL;
}


