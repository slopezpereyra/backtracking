
// Node in a set of elements
struct _node{
    int elem;
    int color;
    struct _node * next;
};

// Node in a set of tuples
struct _edge{
    int a;
    int b;
    struct _edge * next;
};

typedef struct _node * node;
typedef struct _node * set;
typedef struct _edge * edge;
typedef struct _edge * tupleSet;


// Constructors
set emptySet();
tupleSet emptyTupleSet();

// Operators
set add(set s, int elem);
set elim(set s, int elem);
node findLastNode(set V);
tupleSet addEdge(tupleSet e, int a, int b);
void dumpTupleSet(tupleSet e);
void dumpSet(set e);
