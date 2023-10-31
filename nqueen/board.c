#include <stdio.h> 
#include <stdlib.h> 
#include "board.h"
#include <assert.h>
#include <stdbool.h>


board initBoard(){
    board b = (board) malloc(sizeof(struct _board));
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            (b -> matrix)[i][j] = 0;
        }
    }
    return b;
}

board copyBoard(board b){
    board clone = (board) malloc(sizeof(struct _board));
    *clone = *b;
    return(clone);
}

void toggle(board b, int x, int y){
    assert(x < 8 && y < 8);
    if (isQueen(b, x, y)) { return; }
    (b -> matrix)[x][y] = 1;
}

void markForQueen(board b, int x, int y){
    assert(x < 8 && y < 8);
    (b -> matrix)[x][y] = 8;
}

void dumpBoard(board b){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            printf("%d  ", (b -> matrix)[j][i]);
        }printf("\n");
    }printf("\n");
}

void toggleCol(board b, int x){
    assert(x < 8);
    for (int i = 0; i < 8; i++){
        toggle(b, x, i);
    }
}

bool isQueen(board b, int x, int y){
    return ( (b -> matrix)[x][y] == 8 );
}


void toggleRow(board b, int y){
    assert(y < 8);
    for (int i = 0; i < 8; i++){
        toggle(b, i, y);
    }
}

void toggleDiag(board b, int x, int y){
    assert(x < 8 && y < 8);
    int d = y - x, x_start, y_start;
    if (d >= 0){ y_start = d; x_start = 0; }
    else{ y_start = 0; x_start = d * (-1); }
    for (int i = 0; i < 8; i++){
        if (x_start > 7 || y_start > 7){
            break;
        }
        toggle(b, x_start, y_start);
        x_start += 1; y_start +=1;
    }
}

void toggleDiagB(board b, int x, int y){
    int x_start, y_start;
    if (x + y >= 7){
        x_start = 7; y_start = x + y - 7;
    }else{
        x_start = y + x; y_start = 0;
    }
    for (int i = 0; i < 8; i++){
        if (x_start < 0 || y_start > 7){
            break;
        }
        toggle(b, x_start, y_start);
        x_start -= 1; y_start +=1;
    }
}

void placeQueen(board b, int x, int y){
    assert(x < 8 && y < 8);
    toggleCol(b, x);
    toggleRow(b, y);
    toggleDiag(b, x, y);
    toggleDiagB(b, x, y);
    markForQueen(b, x, y);
}



bool canBeSolved(board b){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            if((b -> matrix)[i][j] == 0){
                return(true);
            }
        }
    }
    return(false);
}

int queenCount(board b){
    int n = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            if((b -> matrix)[i][j] == 8){
                n += 1;
            }
        }
    }
    return(n);
}

bool nQueen(board b){
    if (queenCount(b) == 8){
        dumpBoard(b);
        return(true);
    }
    if (!canBeSolved(b)){
        return(false);
    }

    bool solved = false;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            if((b -> matrix)[i][j] == 0){
                board subBoard = copyBoard(b);
                placeQueen(subBoard, i, j);
                solved = true && nQueen(subBoard);
                if (solved) { dumpBoard(b);  return(true); } // early stop
            }
        }
    }
    return(solved);
}

int main(){
    board b = initBoard();
//    dumpBoard(b);
//    printf("Solvable : %d \n", canBeSolved(b));
//    placeQueen(b, 0, 0);
//    dumpBoard(b);
//    printf("Solvable : %d \n", canBeSolved(b));
    nQueen(b);
//

}
