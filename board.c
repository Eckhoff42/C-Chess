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

int n;            // size of the side of the board
char board[8][4]; // TODO: should be n/2

/*
write a piece to a coordinate in the board.
Does not check if the move is valid.
*/
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

/*
get piece at given coordinates.
Returns :
    the piece at the given position
    127 if error
*/
char get_piece(int x, int y)
{
    // se om brikken er utenfor brettet
    if (x > n || y > n || x < 0 || y < 0)
    {
        return 127;
    }

    char tuple = board[y][(x / 2)];
    if (x % 2 == 0)
    {
        return get_left(tuple);
    }
    else
    {
        return get_right(tuple);
    }
}

/*
place the correct pieces at the correct position at the board.
*/
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

/*
see if a piece can be placed at a coordinate
returns:
    1 if valid
    2 if target is empty
    0 if not valid
*/
int valid_place(char piece, int to_x, int to_y)
{
    char existing = get_piece(to_x, to_y);
    if (existing == 0)
        return 2;

    existing = existing & 1; // bit 1-7 settes til 0
    piece = piece & 1;       // bit 1-7 settes til 0
    return piece ^ existing;
}

/*
check if there is a valid straight path between from and to
returns:
    1 if it exists
    0 if it does not exist
*/
int valid_straight(int from_x, int from_y, int to_x, int to_y)
{
    // the move is not straight
    if (from_x != to_x && from_y != to_y)
    {
        return 0;
    }

    char piece = get_piece(from_x, from_y);

    // check if there is a piece at a given position
    if (piece == 127)
    {
        return 0;
    }

    // the move is up
    if (from_y < to_y)
    {
        for (int y = from_y; y <= to_y; y--)
        {
            if (!valid_place(piece, from_x, y))
                return 0;
        }
        return 1;
    }

    // for (int y = from)

    // for (int)
    return 0;
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
