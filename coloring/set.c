#include <stdio.h> 
#include <stdlib.h> 
#include "set.h"

// Do not allocate memory if setting the pointer to NULL.
// It makes no sense to reserve memory at some address X
// and then set the pointer to such address to NULL! 
set emptySet(){
    set s;
    s = NULL; 
    return(s);
}

tupleSet emptyTupleSet(){
    tupleSet s;
    s = NULL; 
    return(s);
}


node findLastNode(set V){
    node p = V;
    while (p -> next != NULL){
        p = p -> next;
    }
    return(p);
}


int lastElement(set V){
    node p = findLastNode(V);
    return(p -> elem);
}

set add(set V, int w){
    if (V == NULL){
        V = (set) malloc(sizeof( struct _node ));
        V -> elem = w;
        V -> next = NULL;
        V -> color = -1;
        return(V);
    }
    node p = V;
    while (p -> next != NULL){
        if (p -> elem == w){ return(V); }
        p = p -> next;
    }
    node newNode = (node) malloc(sizeof( struct _node ));
    newNode -> elem = w;
    newNode -> next = NULL;
    newNode -> color = -1;
    p -> next = newNode;
    return(V);
}

set elim(set V, int w){
    if (V -> elem == w){
        node p = V;
        V = V -> next;
        free(p);
        return(V);
    }
    node target = V;
    node predecessor;
    while (target -> elem != w){
        predecessor = target;
        target = target -> next;
    }
    predecessor -> next = target -> next;
//    printf("%d\n", target -> elem);
    free(target);
    return(V);
}

void dumpSet(set s){
    node p = s; 
    while (p != NULL){
        printf("Vertex %d with color %d\n", p -> elem, p -> color);
        p = p -> next;
    }
    printf("\n");

} 

// Edges 

tupleSet addEdge(tupleSet E, int a, int b){
    if (E == NULL){
        E = (tupleSet) malloc(sizeof( struct _edge ));
        E -> a = a;
        E -> b = b;
        E -> next = NULL;
        return(E);
    }
    edge p = E;
    while (p -> next != NULL){
        if (p -> a == a && p -> b == b){ return(E); }
        p = p -> next;
    }
    edge newEdge = (edge) malloc(sizeof( struct _edge ));
    newEdge -> a = a;
    newEdge -> b = b;
    newEdge -> next = NULL;
    p -> next = newEdge;
    return(E);
}

void dumpTupleSet(tupleSet s){
    edge p = s; 
    while (p != NULL){
        printf("(%d, %d), ", p -> a, p -> b);
        p = p -> next;
    }
    printf("\n");

} 


