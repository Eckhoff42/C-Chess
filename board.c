#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

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
const char EMPTY = 0;  // 0000
const char PAWN = 2;   // 0100
const char ROOK = 4;   // 0010
const char BISHOP = 6; // 0110
const char KNIGHT = 8; // 0001
const char QUEEN = 12; // 0011
const char KING = 14;  // 0111

int n;            // size of the side of the board
char board[8][4]; // TODO: should be n/2

/*
write a piece to a coordinate in the board.
Does not check if the move is valid.
returns
    1 if success
    0 if fail
*/
char place_piece(char piece, int x, int y)
{
    // se om brikken er utenfor brettet
    if (!inside_board(x, y, n))
    {
        return 0;
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
    return 1;
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
    if (!inside_board(x, y, n))
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
        place_piece(turn_black(PAWN), x, 1);
        place_piece(PAWN, x, 6);
    }

    // sett inn Tårn, Hest, Springer
    for (y = 0; y < n; y += 7)
    {
        place_piece(ROOK, 0, y);
        place_piece(ROOK, 7 - 0, y);

        place_piece(KNIGHT, 1, y);
        place_piece(KNIGHT, 7 - 1, y);

        place_piece(BISHOP, 2, y);
        place_piece(BISHOP, 7 - 2, y);
    }
    // sett inn Konge og Dronning
    place_piece(KING, 3, 0);
    place_piece(KING, 4, 7);
    place_piece(QUEEN, 3, 7);
    place_piece(QUEEN, 4, 0);

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
    if (!inside_board(to_x, to_y, n))
        return 0;

    char existing = get_piece(to_x, to_y);
    if (existing == 0)
        return 2;

    existing = existing & 1; // bit 1-7 settes til 0
    piece = piece & 1;       // bit 1-7 settes til 0
    return piece ^ existing;
}

int valid_move_switch(char piece, int x, int y, int end, char end_coordinate)
{
    switch (valid_place(piece, x, y))
    {
    // empty piece
    case 2:
        return 1;

    // enemy piece
    case 1:
        if (end_coordinate == 'x')
        {
            return (x == end);
        }
        else
        {
            return (y == end);
        }

    // own piece (returnvalue 0)
    default:
        return 0;
    }
}

/*
check if there is a valid straight path between from and to
returns:
    1 if it exists
    0 if it does not exist
*/
int valid_straight(int from_x, int from_y, int to_x, int to_y)
{
    // the move is not straight or no move at all
    if ((from_x != to_x && from_y != to_y) || (from_x == to_x && from_y == to_y))
    {
        return 0;
    }

    // check if there is a piece at the given position
    char piece = get_piece(from_x, from_y);
    if (piece == 127)
        return 0;

    // move is up
    if (from_y > to_y)
    {
        for (int y = from_y - 1; y >= to_y; y--)
        {
            if (!valid_move_switch(piece, from_x, y, to_y, 'y'))
                return 0;
        }
    }

    // move is down
    else if (from_y < to_y)
    {
        for (int y = from_y + 1; y <= to_y; y++)
        {
            if (!valid_move_switch(piece, from_x, y, to_y, 'y'))
                return 0;
        }
    }

    // move is left
    else if (from_x > to_x)
    {
        for (int x = from_x - 1; x >= to_x; x--)
        {
            if (!valid_move_switch(piece, x, from_y, to_x, 'x'))
                return 0;
        }
    }

    // move is right
    else if (from_x < to_x)
    {
        for (int x = from_x + 1; x <= to_x; x++)
        {
            if (!valid_move_switch(piece, x, from_y, to_x, 'x'))
                return 0;
        }
    }

    return 1;
}

/*
check if there is a valid diagonal path between from and to
returns:
    1 if it exists
    0 if it does not exist
*/
int valid_diagonal(int from_x, int from_y, int to_x, int to_y)
{
    int horizontal = from_x - to_x;
    int vertical = from_y - to_y;

    // not horizontal move or no move at all
    if ((abs(horizontal) != abs(vertical)) || (from_x == to_x && from_y == to_y))
        return 0;

    char piece = get_piece(from_x, from_y);
    // no piece at given position
    if (piece == 127)
        return 0;

    // down right
    if (from_x < to_x && from_y < to_y)
    {
        printf("down right\n");
        for (int offset = 1; offset <= (to_x - from_x); offset++)
        {
            if (!valid_move_switch(piece, from_x + offset, from_y + offset, to_y, 'y'))
                return 0;
        }
    }

    // down left
    if (from_x > to_x && from_y < to_y)
    {
        printf("down left\n");
        for (int offset = 1; offset <= (from_x - to_x); offset++)
        {
            if (!valid_move_switch(piece, from_x - offset, from_y + offset, to_y, 'y'))
                return 0;
        }
    }

    // up right
    if (from_x < to_x && from_y > to_y)
    {
        printf("up right\n");
        for (int offset = 1; offset <= (to_x - from_x); offset++)
        {
            if (!valid_move_switch(piece, from_x + offset, from_y - offset, to_y, 'y'))
                return 0;
        }
    }

    // up left
    if (from_x > to_x && from_y > to_y)
    {
        printf("up left\n");
        for (int offset = 1; offset <= (from_x - to_x); offset++)
        {
            if (!valid_move_switch(piece, from_x - offset, from_y - offset, to_y, 'y'))
                return 0;
        }
    }

    return 1;
}

/*
checks if a L-move is valid
returns
    0 - not valid
    1 - valid enemy
    2 - valid empty
*/
int valid_L_shape(int from_x, int from_y, int to_x, int to_y)
{
    // outside board
    if (!inside_board(from_x, from_y, n) || !inside_board(to_x, to_y, n))
        return 0;

    // not int the L shape
    if (abs(from_x - to_x) + abs(from_y - to_y) != 3)
    {
        return 0;
    }

    char piece = get_piece(from_x, from_y);
    // no piece at given from position
    if (piece == 127)
        return 0;

    return valid_place(piece, to_x, to_y);
}

void play()
{
    int done = 0;
    int round = 0;

    init_board(n);

    while (!done)
    {
        round++;
        print_board(board);

        int valid_move = 0;
        int x, y, to_x, to_y = -1;
        while (!valid_move)
        {
            printf("specify from\n");
            int res = scanf("%d,%d", &x, &y);

            if (!res)
            {
            }

            printf("specify to\n");
            res = scanf("%d,%d", &to_x, &to_y);

            printf("%d | (%d, %d) -> (%d %d)\n", res, x, y, to_x, to_y);

            valid_move = valid_straight(x, y, to_x, to_y);
            if (!valid_move)
            {
                printf("Move is not allowed. Try again\n ");
            }
        }

        char peace = get_piece(x, y);
        place_piece(peace, to_x, to_y);
        place_piece(EMPTY, x, y);
    }
}

int main(int argc, char const *argv[])
{
    n = 8;

    play();

    return 0;
}
