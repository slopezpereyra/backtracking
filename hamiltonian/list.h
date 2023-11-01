
// list
struct _node {
    int value;
    struct _node* next;
};

typedef struct _node * node;
typedef struct _node * list;
typedef node list;



list append(list l, node n);
list del(list l, int x);
int llength(list l);
bool list_has(list l, int x);
