#include <stdio.h>
#include "help_methods.h"
#include "bit_functions.h"

/*
create an array matching base10 value of piece with a character
*/
void init_pieces(char *p)
{
    p[0] = ' ';  // EMPTY
    p[2] = 'P';  // PAWN white
    p[3] = 'p';  // PAWN black
    p[4] = 'R';  // ROOK white
    p[5] = 'r';  // ROOK black
    p[6] = 'B';  // BISHOP white
    p[7] = 'b';  // BISHOP black
    p[8] = 'H';  // KNIGHT white
    p[9] = 'h';  // KNIGHT black
    p[12] = 'Q'; // QUEEN white
    p[13] = 'q'; // QUEEN black
    p[14] = 'K'; // KING white
    p[15] = 'k'; // KING black
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
    char pieces[255] = "";
    init_pieces(pieces);

    printf("\033[1;33m    |x0 |x1 |x2 |x3 |x4 |x5 |x6 |x7 |\n \033[0m");

    for (int y = 0; y < 8; y++)
    {
        print_repeating_char('-', 37);
        printf("\n|\033[1;36my%d \033[0m", y);

        for (int x = 0; x < sizeof(board[0]); x++)
        {
            char tuple = board[y][x];
            char left = get_left(tuple);
            char right = get_right(tuple);

            printf("| %c ", pieces[(int)left]);
            printf("| %c ", pieces[(int)right]);
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
