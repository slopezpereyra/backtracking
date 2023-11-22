#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include <stdbool.h>

// Struct with 8x8 array as only field.
struct _board {
    int matrix[8][8];
};

typedef struct _board * board;

/* Initializes an empty board 
 * with all entries equal to zero.
 */
board initBoard(){
    board b = (board) malloc(sizeof(struct _board));
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            (b -> matrix)[i][j] = 0;
        }
    }
    return b;
}

/* Determines whether a queen is placed at coordinate (x, y) of a 
 * board.
 */
int hasQueen(board b, int x, int y){
    return ( (b -> matrix)[x][y] == 8 );
}

/* Makes deep copy of a board.
 */
board copyBoard(board b){
    board clone = (board) malloc(sizeof(struct _board));
    *clone = *b;
    return(clone);
}

/* Sets coordinate (x, y) of a board to 1.
 */
void toggle(board b, int x, int y){
    assert(x < 8 && y < 8);
    if (hasQueen(b, x, y)) { return; }
    (b -> matrix)[x][y] = 1;
}

/* Sets coordinate (x, y) of a board to 8, where 8 represents a queen.
 */
void markForQueen(board b, int x, int y){
    assert(x < 8 && y < 8);
    (b -> matrix)[x][y] = 8;
}

/* Prints the matrix of a board.
 */
void dumpBoard(board b){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j ++){
            printf("%d  ", (b -> matrix)[j][i]);
        }printf("\n");
    }printf("\n");
}

/* Sets all entries in xth column to one.
 */
void toggleCol(board b, int x){
    assert(x < 8);
    for (int i = 0; i < 8; i++){
        toggle(b, x, i);
    }
}

/* Sets all entries in yth row to one.
 */
void toggleRow(board b, int y){
    assert(y < 8);
    for (int i = 0; i < 8; i++){
        toggle(b, i, y);
    }
}

/* Finds the diagonal that passes through (x, y) from left to right
 * and sets all its entries to 1.
 */
void toggleDiag(board b, int x, int y){
    assert(x < 8 && y < 8);
    int x_start, y_start;
    if (y >= x){ y_start = y - x; x_start = 0; }
    else{ y_start = 0; x_start = x - y; }
    for (int i = 0; i < 8; i++){
        if (x_start > 7 || y_start > 7){
            break;
        }
        toggle(b, x_start, y_start);
        x_start += 1; y_start +=1;
    }
}

/* Finds the diagonal that passes through (x, y) from right to left
 * and sets all its entries to 1.
 */
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

/* Sets (x, y) to 8; the entries of the row, column and diagonals passing
 * through (x, y) are all set to 1.
 */
void placeQueen(board b, int x, int y){
    assert(x < 8 && y < 8);
    toggleCol(b, x);
    toggleRow(b, y);
    toggleDiag(b, x, y);
    toggleDiagB(b, x, y);
    markForQueen(b, x, y);
}

/* Determines if there is place for another queen in a given board.
 */
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

/* Determines the number of queens in a board.
 */
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

/* Frees memory of a board and sets its pointer to null.
 */
void destroyBoard(board b){
    free(b);
    b = NULL;
}

/* Backtracking algorithm. Finds and prints all arrangements of eight queens in
 * an 8x8 board s.t. no queen attacks another.
 */
bool nQueen(board b, int x, int y){
    placeQueen(b, x, y);
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
                solved = nQueen(subBoard, i, j);
                destroyBoard(subBoard);
                if (solved) { return(true); }
            }
        }
    }return(false);
}


int main(){
    board b = initBoard();
    nQueen(b, 5, 3);
    board b2 = initBoard();
    nQueen(b2, 0, 0);
}
