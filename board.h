char place_piece(char piece, int x, int y);
char get_piece(int x, int y);
void init_board(int n);
int valid_place(char piece, int to_x, int to_y);
int valid_move(int from_x, int from_y, int to_x, int to_y);
int move_piece(int from_x, int from_y, int to_x, int to_y);
