#include <stdio.h>
#include "help_methods.h"

void print_bytes(char c) {

    for(int bit=0;bit<8; bit++)
    {
        printf("%i ", c & 0x01);
        c = c >> 1;
    }
    printf("\n");
}

// TODO: use a dictionary map bytes to its representation

void print_board(char board[8][4]) {
	for (int x = 0; x < sizeof(board); x++) {
		printf("-------------------------\n");
		for (int y = 0; y < sizeof(board[0]); y++) {
			
			char touple = board[x][y];
			char left = touple & 240;
			char right = touple << 4;
			
			char sign = ' ';
			if (touple == 1) {
				sign = 'b';
			}
			
			printf("| %c | %c ", left, right);

		}
		printf("|\n");
	}
	printf("-------------------------\n");
}
