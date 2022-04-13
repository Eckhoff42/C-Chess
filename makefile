GCC_FLAGS = -g -Wall
VALGRIND_FLAGS = --leak-check=full

all: board

board: board.c help_methods.c bit_functions.c test_chess.c
	gcc $(GCC_FLAGS) board.c help_methods.c bit_functions.c test_chess.c -o board.o

run: board
	./board.o

vrun: board
	valgrind $(VALGRIND_FLAGS) ./board.o

runtest: board
	./board.o test

clean:
	rm -f *.o