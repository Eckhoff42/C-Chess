GCC_FLAGS = -g -Wall
VALGRIND_FLAGS = --leak-check=full

all: board

board: board.c help_methods.c bit_functions.c
	gcc $(GCC_FLAGS) board.c help_methods.c bit_functions.c -o board

run: board
	./board

vrun: board
	valgrind $(VALGRIND_FLAGS) ./board

