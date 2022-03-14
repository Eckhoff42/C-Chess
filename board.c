#include <stdio.h>
#include "help_methods.h"

//number of different pieces
// bonde        x100
// tårn         x010
// hest         x001
// springer     x110
// dronning     x011
// konge        x111
// tom          x000
// white starts with 0
// black stars with 1

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

const char TOM = 0;
const char BONDE = 2;	    // 0100
const char SPRINGER = 6;    // 0110
const char TAARN = 4;	    // 0010
const char HEST = 8;	    // 0001
const char DRONNING = 12;   // 0011
const char KONGE = 14;      // 0111

int n;
char board[8][4]; // TODO: should be n/2

char turn_black(char c) {
	return c | 1;
}

char turn_white(char c) {
	return c & 254;
}

char move_right(char c) {
	return c << 4;
}

void insert_left(char piece, char *tuple) {
        char eraser = 240; // = 00001111
	*tuple = *tuple & eraser; // første 4 bit satt til 0
	*tuple = *tuple | piece; // sett inn brikken
}

void insert_right(char piece, char *tuple) {
	char eraser = 15;
	*tuple = *tuple & eraser; // siste 4 bit satt til 0 
	piece = move_right(piece); 
	*tuple = *tuple | piece ; // sett inn brikken
}

char place_piece(char piece, int x, int y) {
	// se om brikken er utenfor brettet
	if (x > n  || y > n || x < 0 || y < 0) {
		return 1;
	}

	char *touple = &board[x][(y/2)];
	if (y % 2 == 0) {
		insert_left(piece, touple);
	} else {
		insert_right(piece, touple);
	}
	return 0;
}

void init_board(int n)
{
    int y, x;
    // brettet er initielt satt til tom
    // TODO: bytt ut med calloc
    for(y = 0; y < n; y++)
    {
        for(x=0; x < n; x++)
        {
            board[y][x] = 0;
        }
    }
   
    // sett inn bønder 
    for (x = 0; x < n; x++) {
    	place_piece(BONDE, x, 1);
	place_piece(BONDE, x, 6);
    }
}



int main(int argc, char const *argv[])
{      
    n = 8;
    init_board(n);
    print_board(board);
    return 0;
}
