#include <stdio.h>

#define EMPTY 0  // 0000 - tom
#define PAWN 2   // 0100 - bonde
#define ROOK 6   // 0110 - tårn
#define QUEEN 14 // 0111 - dronning
#define KING 10  // 0101 - konge
#define BISHOP 8 // 0001 - løper
#define KNIGHT 4 // 0010 - hest

void print_bytes(char c);
void print_n_bit(char c, int n);
void print_board(char board[8][4]);
void board_dump(char board[8][4]);
int inside_board(int x, int y, int n);