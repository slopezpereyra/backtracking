#include <stdbool.h>

// list
struct _node {
    int value;
    struct _node* next;
};

typedef struct _node * node;
typedef struct _node * list;
typedef node list;

struct _graph {
    int V;
    node *adj_l; // pointer to a pointer to node
};

typedef struct _graph * graph;

// 
//
//

int llength(list l);
bool list_has(list l, int x);
graph createGraph(int n);
void addEdge(graph g, int src, int dest);
void removedge(graph g, int src, int dest);
void printGraph(graph g);
node createNewNode(int value);
graph cloneGraphWithoutNode(graph original, int removeIndex);
list append(list l, node n);
list del(list l, int x);

