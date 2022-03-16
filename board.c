#include <stdio.h>
#include <strings.h>

#include "help_methods.h"
#include "bit_functions.h"

// et brett ser slikt ut
//---------------------------------
//| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | <-- x verdier
//---------------------------------
//| 1 |   |   |   |   |   |   |   |
//---------------------------------
//| 2 |   |   |   |   |   |   |   |
//---------------------------------
//| 3 |   |   |   |   |   |   |   |
//---------------------------------
//| 4 |   |   |   |   |   |   |   |
//---------------------------------
//| 5 |   |   |   |   |   |   |   |
//---------------------------------
//| 6 |   |   |   |   |   |   |   |
//---------------------------------
//| 7 |   |   |   |   |   |   |   |
//---------------------------------
//  ^--- y verdier

// representert som et array av bytes -
// 1 byte = 2 brikker
// brikke x=1,y=4 hentes slik;
//   p = board[4/2][1] ; get_right(p) ;
// board[y][x];

//|---------------|
//| 0 | 1 | 2 | 3 |  <-- x verdier
//|---------------|
//| 1 |   |   |   |
//|---------------|
//| 2 |   |   |   |
//|---------------|
//| 3 |   |   |   |
//|---------------|
//| 4 |   |   |   |
//|---------------|
//| 5 |   |   |   |
//|---------------|
//| 6 |   |   |   |
//|---------------|
//| 7 |   |   |   |
//|---------------|
//  ^--- y verdier

// BLACK                  // 1xxx
// WHITE                  // 0xxx
const char TOM = 0;       // 0000
const char BONDE = 2;     // 0100
const char TAARN = 4;     // 0010
const char SPRINGER = 6;  // 0110
const char HEST = 8;      // 0001
const char DRONNING = 12; // 0011
const char KONGE = 14;    // 0111

int n;
char board[8][4]; // TODO: should be n/2

char place_piece(char piece, int x, int y)
{
    // se om brikken er utenfor brettet
    if (x > n || y > n || x < 0 || y < 0)
    {
        return 1;
    }

    char *tuple = &board[y][(x / 2)];
    if (x % 2 == 0)
    {
        insert_left(piece, tuple);
    }
    else
    {
        insert_right(piece, tuple);
    }
    return 0;
}

void init_board(int n)
{
    int y, x;

    // brettet er initielt satt til tom
    bzero(&board, sizeof(board));

    // sett inn bønder
    for (x = 0; x < n; x++)
    {
        place_piece(turn_black(BONDE), x, 1);
        place_piece(BONDE, x, 6);
    }

    // sett inn Tårn, Hest, Springer
    for (y = 0; y < n; y += 7)
    {
        place_piece(TAARN, 0, y);
        place_piece(TAARN, 7 - 0, y);

        place_piece(HEST, 1, y);
        place_piece(HEST, 7 - 1, y);

        place_piece(SPRINGER, 2, y);
        place_piece(SPRINGER, 7 - 2, y);
    }
    // sett inn Konge og Dronning
    place_piece(KONGE, 3, 0);
    place_piece(KONGE, 4, 7);
    place_piece(DRONNING, 3, 7);
    place_piece(DRONNING, 4, 0);

    // brikker på y = 0 gjøres svarte
    for (x = 0; x < n / 2; x++)
    {
        board[0][x] = board[0][x] | 17;
    }
}

int valid_straight(char *piece, int from_x, int from_y, int to_x, int to_y)
{
    if (from_x != to_x && from_y != to_y)
    {
        return -1;
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    n = 8;
    init_board(n);
    // board_dump(board);
    print_board(board);
    printf("\n");
    return 0;
}
