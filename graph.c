#include <stdio.h> 
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>

void dump_list(list l){
    while (l != NULL){
        printf("%d -> ", l -> value);
        l = l -> next;
    }printf("\n");
}

int llength(list l){
    int n = 0;
    while (l != NULL){
        n = n + 1;
        l = l -> next;
    }
    return(n);
}

bool list_has(list l, int x){
    bool has = (l -> value) == x;
    while(l -> next != NULL && !has){
        l = l -> next;
        has = (l -> value) == x;
    }
    return(has);
}

list append(list l, node n){
    if (l == NULL){
        return(n);
    }
    node aux = l;
    while (aux -> next != NULL){
        aux = aux -> next;
    }
    aux -> next = n;
    return(l);
}

list del(list l, int x){
    if (!list_has(l, x)){
        return(l);
    }
    node laux = l;
    if (laux -> value == x){
        laux = laux -> next;
        free(l);
        return(laux);
    }

    while ((laux -> next) -> value != x){
        laux = laux -> next;
    }
    node _laux  = laux; 
    _laux -> next = (_laux -> next) -> next;
    free(laux -> next);
    return(l);
}

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

graph cloneGraphWithoutNode(graph original, int removeIndex) {
    if (original == NULL || removeIndex < 0 || removeIndex >= original->V) {
        // Handle invalid input or NULL graph.
        return NULL;
    }

    int n = original->V; // The new number of vertices
    graph newGraph = createGraph(n);

    for (int i = 0 ; i < original->V; i++) {
        if (i == removeIndex) {
            // Skip the removed vertex
            continue;
        }
        list l = (original -> adj_l)[i];
        (newGraph -> adj_l)[i] = l;
    }

    return newGraph;
}

void removeVertex(graph g, int i){
    (g -> adj_l)[i] = NULL;
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


