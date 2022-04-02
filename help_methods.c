#include <stdio.h>
#include "help_methods.h"
#include "bit_functions.h"

#define WHITE_COLOR = "\033[34m"

void init_pieces(char *p[16])
{
    p[EMPTY] = " ";                            // EMPTY
    p[PAWN] = "\033[34mP\033[0m";              // PAWN white
    p[PAWN + 1] = "\033[1m\033[31mp\033[0m";   // PAWN black
    p[ROOK] = "\033[34mR\033[0m";              // ROOK white
    p[ROOK + 1] = "\033[1m\033[31mr\033[0m";   // ROOK black
    p[BISHOP] = "\033[34mB\033[0m";            // BISHOP white
    p[BISHOP + 1] = "\033[1m\033[31mb\033[0m"; // BISHOP black
    p[KNIGHT] = "\033[34mH\033[0m";            // KNIGHT white
    p[KNIGHT + 1] = "\033[1m\033[31mh\033[0m"; // KNIGHT black
    p[QUEEN] = "\033[34mQ\033[0m";             // QUEEN white
    p[QUEEN + 1] = "\033[1m\033[31mq\033[0m";  // QUEEN black
    p[KING] = "\033[34mK\033[0m";              // KING white
    p[KING + 1] = "\033[1m\033[31mk\033[0m";   // KING black
}

/*
print a byte as binary
*/
void print_bytes(char c)
{

    for (int bit = 0; bit < 8; bit++)
    {
        printf("%i ", c & 0x01);
        c = c >> 1;
    }
}

/*
print n bit of a byte
*/
void print_n_bit(char c, int n)
{

    for (int bit = 0; bit < n; bit++)
    {
        printf("%i ", c & 0x01);
        c = c >> 1;
    }
}

/*
print the same char n times;
*/
void print_repeating_char(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

// TODO: use a dictionary map bytes to its representation
/*
print the bytes of the board. in the 4 * 8 format
*/
void board_dump(char board[8][4])
{

    for (int i = 0; i < 8; i++)
    {
        printf(" | ");
        for (int j = 0; j < 4; j++)
        {
            print_bytes(board[i][j]);
            printf(" | ");
        }
        printf("\n");
    }
}

/*
pretty print the board.
Piece symbols are defined in init_pieces
*/
void print_board(char board[8][4])
{
    char *pieces[16];
    init_pieces(pieces);

    printf("\033[1;33m    |x0 |x1 |x2 |x3 |x4 |x5 |x6 |x7 |\n \033[0m");

    for (int y = 0; y < 8; y++)
    {
        print_repeating_char('-', 37);
        printf("\n|\033[1;33my%d \033[0m", y);

        for (int x = 0; x < sizeof(board[0]); x++)
        {
            char tuple = board[y][x];
            char left = get_left(tuple);
            char right = get_right(tuple);

            printf("| %s ", pieces[(int)left]);
            printf("| %s ", pieces[(int)right]);
        }
        printf("|\n");
    }
    print_repeating_char('-', 37);
    printf("\n");
}

/*
returns if the position is inside the board
returns
    1 if inside
    0 if outside
*/
int inside_board(int x, int y, int n)
{
    return !(x > n || y > n || x < 0 || y < 0);
}
