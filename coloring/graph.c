#include <stdio.h> 
#include <stdlib.h> 
#include "graph.h"
#include <stdbool.h>

// Idea : At each node we will have candidate colors;
// i.e. those colors that aren't the color of a neighbor.
// At each node we "try" each candidate color but we
// must stop once all nodes are colored.
//

node getVertex(struct graph g, int i){
    node p = g.G;
    for (int j = 0; j < i; j++){
        p = p -> next;
    }return(p);
}

bool constraintBroken(struct graph g){
    for (edge p = g.E; p != NULL; p = p->next) {
        node a = getVertex(g, p -> a);
        node b = getVertex(g, p -> b);
        if (a -> color == -1 || b -> color == -1){
            continue;
        }
        if (a -> color == b -> color){
            return(true);
        }
    }
    return(false);
}

struct graph colorVertex(struct graph g, int vertex, int color){
    node v = getVertex(g, vertex);
    v -> color = color;
    return(g);
}


bool colorGraph(struct graph g, int at, int m){

    if (constraintBroken(g)){
        return(false);
    }
    if (at < 0 ){
        dumpSet(g.G);
        return(true);
    }

    bool result = false;
    
    for (int i = m; i >= 0; i--){
       result = result || colorGraph( colorVertex(g, at, i), at - 1, m);
       if (result) { return(true); }
    }
    return(false);
}


int main(){

    set s = emptySet();
    s = add(s, 0);
    s = add(s, 1);
    s = add(s, 2);
    s = add(s, 3);
    s = add(s, 4);

    tupleSet e = emptyTupleSet();
    e = addEdge(e, 0, 1);
    e = addEdge(e, 0, 2);
    e = addEdge(e, 1, 2);
    e = addEdge(e, 2, 3);
    e = addEdge(e, 3, 4);
    dumpTupleSet(e);

    printf("Starting coloring process...\n");
    struct graph g; g.G = s; g.E = e;
    colorGraph(g, 4, 5);

}
