FLAGS= -g -Wall

all: board

board: board.c help_methods.c
	gcc $(FLAGS) board.c help_methods.c -o board

run: board
	./board

