#include <stdbool.h>

struct _board {
    int matrix[8][8];
};

typedef struct _board * board;

void dumpBoard(board b);
void toggle(board b, int x, int y);
bool isQueen(board b, int x, int y);
board initBoard();
