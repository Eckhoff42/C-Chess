#include "test_chess.h"
#include "board.h"
#include "help_methods.h"
#include "bit_functions.h"

#include <assert.h>
#include <string.h>

char board[8][4];
char test_results[100];

void initiate_test()
{
  init_board(8);
  memset(&test_results, 2, sizeof(test_results));
  printf("*************** Starting Test ***************\n");
}

void reset_board()
{
  bzero(&board, sizeof(board));
}

void test_pawn_move()
{
  place_piece(PAWN, 3, 6);
  int valid = valid_move(3, 6, 3, 4);
  assert(valid != 0);
  int moved = move_piece(3, 6, 3, 4);
  assert(moved != 0);
  printf("Test: Pawn move passed\n");
}

void test_pawn_en_passant()
{
  place_piece(PAWN, 3, 6);
  int from_x = 3;
  int from_y = 6;
  int to_x = 3;
  int to_y = 4;
  int valid = valid_move(from_x, from_y, to_x, to_y);
  assert(valid != 0);
  int moved = move_piece(from_x, from_y, to_x, to_y);
  assert(moved != 0);
  printf("Test: Pawn en passant passed\n");
}

void test_king_moves()
{
  place_piece(KING, 3, 3);
  int from_x = 3;
  int from_y = 3;
  int valid = valid_move(from_x, from_y, 3, 4);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 3, 2);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 4, 2);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 4, 3);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 4, 4);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 2);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 3);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 4);

  printf("Test: King move passed\n");
}

void test_bishop_moves()
{
  place_piece(BISHOP, 3, 3);
  int from_x = 3;
  int from_y = 3;
  int valid = valid_move(from_x, from_y, 4, 2);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 1, 5);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 7, 7);
  assert(valid != 0);

  place_piece(PAWN, 2, 2);
  valid = valid_move(from_x, from_y, 1, 1);
  assert(valid == 0);
  valid = valid_move(from_x, from_y, 2, 2);
  assert(valid == 0);
  printf("Test: Bishop move passed\n");
}

void test_rook_moves()
{
  place_piece(ROOK, 3, 3);
  int from_x = 3;
  int from_y = 3;
  int valid = valid_move(from_x, from_y, 3, 0);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 3, 4);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 7, 3);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 3);
  assert(valid != 0);

  place_piece(PAWN, 3, 5);
  valid = valid_move(from_x, from_y, 3, 4);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 3, 7);
  assert(valid == 0);
  valid = valid_move(from_x, from_y, 3, 5);
  assert(valid == 0);
}

void test_knight_moves()
{
  place_piece(KNIGHT, 4, 7);
  int from_x = 4;
  int from_y = 7;
  int valid = valid_move(from_x, from_y, 5, 5);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 3, 5);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 9, 5);
  assert(valid == 0);

  printf("Test: Knight move passed\n");
}

void test_queen_moves()
{
  place_piece(QUEEN, 4, 4);
  int from_x = 4;
  int from_y = 4;
  int valid = valid_move(from_x, from_y, 4, 2);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 5);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 7, 7);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 4, 1);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 4, 8);
  assert(valid == 0);
  valid = valid_move(from_x, from_y, -1, -1);
  assert(valid == 0);

  place_piece(PAWN, 3, 5);
  valid = valid_move(from_x, from_y, 3, 6);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 2, 6);
  assert(valid == 0);
  valid = valid_move(from_x, from_y, 2, 5);
  assert(valid != 0);
  valid = valid_move(from_x, from_y, 3, 8);

  printf("Test: Queen move passed\n");
}

void test_pawn_take()
{
  place_piece(PAWN, 3, 3);

  // positive tests
  place_piece(turn_black(PAWN), 4, 2);
  int valid = valid_move(3, 3, 4, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 2, 2);
  valid = valid_move(3, 3, 2, 2);
  assert(valid != 0);

  // negative tests
  place_piece(turn_black(PAWN), 2, 4);
  valid = valid_move(3, 3, 2, 4);
  assert(valid == 0);

  place_piece(turn_black(PAWN), 4, 4);
  valid = valid_move(3, 3, 4, 4);
  assert(valid == 0);

  place_piece(turn_black(PAWN), 3, 2);
  valid = valid_move(3, 3, 3, 2);
  assert(valid == 0);

  printf("Test: Pawn take passed\n");
}

void test_king_take()
{
  place_piece(KING, 3, 3);

  // positive tests
  place_piece(turn_black(PAWN), 4, 2);
  int valid = valid_move(3, 3, 4, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 2, 2);
  valid = valid_move(3, 3, 2, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 3, 2);
  valid = valid_move(3, 3, 3, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 2, 4);
  valid = valid_move(3, 3, 2, 4);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 4, 4);
  valid = valid_move(3, 3, 4, 4);
  assert(valid != 0);

  // negative tests
  place_piece(turn_black(PAWN), 1, 3);
  valid = valid_move(3, 3, 1, 3);
  assert(valid == 0);

  place_piece(PAWN, 4, 4);
  valid = valid_move(3, 3, 4, 4);
  assert(valid == 0);

  printf("Test: King take passed\n");
}

void test_rook_take()
{
  place_piece(ROOK, 3, 3);

  // positive tests
  place_piece(turn_black(PAWN), 3, 0);
  int valid = valid_move(3, 3, 3, 0);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 3, 4);
  valid = valid_move(3, 3, 3, 4);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 7, 3);
  valid = valid_move(3, 3, 7, 3);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 2, 3);
  valid = valid_move(3, 3, 2, 3);
  assert(valid != 0);

  place_piece(PAWN, 3, 5);
  place_piece(turn_black(PAWN), 3, 4);
  valid = valid_move(3, 3, 3, 4);
  assert(valid != 0);

  place_piece(PAWN, 2, 3);
  valid = valid_move(3, 3, 2, 3);
  assert(valid == 0);

  printf("Test: Rook take passed\n");
}

void test_queen_take()
{
  place_piece(QUEEN, 4, 4);

  // positive tests
  place_piece(turn_black(PAWN), 4, 2);
  int valid = valid_move(4, 4, 4, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 2, 5);
  valid = valid_move(4, 4, 2, 5);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 7, 7);
  valid = valid_move(4, 4, 7, 7);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 4, 1);
  valid = valid_move(4, 4, 4, 1);
  assert(valid == 0);

  place_piece(PAWN, 3, 5);
  place_piece(turn_black(PAWN), 3, 6);
  valid = valid_move(4, 4, 3, 6);
  assert(valid == 1);

  // negative tests
  place_piece(PAWN, 4, 2);
  place_piece(turn_black(PAWN), 4, 1);
  valid = valid_move(4, 4, 4, 1);
  assert(valid == 0);
}

void test_bishop_take()
{
  place_piece(BISHOP, 3, 3);

  // positive tests
  place_piece(turn_black(PAWN), 4, 2);
  int valid = valid_move(3, 3, 4, 2);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 1, 5);
  valid = valid_move(3, 3, 1, 5);
  assert(valid != 0);

  place_piece(turn_black(PAWN), 7, 7);
  valid = valid_move(3, 3, 7, 7);
  assert(valid != 0);

  place_piece(PAWN, 2, 2);
  place_piece(turn_black(PAWN), 1, 1);
  valid = valid_move(3, 3, 1, 1);
  assert(valid == 0);

  place_piece(PAWN, 4, 4);
  valid = valid_move(3, 3, 4, 4);
  assert(valid == 0);
}

void test_moves()
{
  reset_board();
  test_pawn_move();
  reset_board();
  test_pawn_en_passant();
  reset_board();
  test_king_moves();
  reset_board();
  test_bishop_moves();
  reset_board();
  test_rook_moves();
  reset_board();
  test_knight_moves();
  reset_board();
  test_queen_moves();
  reset_board();
}

void test_take()
{
  test_pawn_take();
  reset_board();
  test_king_take();
  reset_board();
  test_rook_take();
  reset_board();
  test_queen_take();
  reset_board();
  test_bishop_take();
}

void run_all_tests()
{
  test_moves();
  test_take();

  printf("\n\033[1;32mAll tests passed!\033[0m\n");
}