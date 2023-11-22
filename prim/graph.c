#include <stdio.h> 
#include <stdlib.h>
#include "graph.h"
#include <stdbool.h>

struct edge{
    unsigned int v1;
    unsigned int v2;
    unsigned int w;
};


struct wgraph{
    list V;
    list E;
}

