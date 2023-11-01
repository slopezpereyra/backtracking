#include <stdlib.h> 
#include <stdbool.h> 
#include<stdio.h>
#include "list.h"

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

