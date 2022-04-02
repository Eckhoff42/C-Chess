/*
set leftmost bit to 1
*/
char turn_black(char c)
{
	return c | 1;
}

/*
set leftmost bit to 0
*/
char turn_white(char c)
{
	return c & 254;
}

/*
move a piece(4bit) from the right to the left
the last 4 bit are set to 0
*/
char move_right(char c)
{
	return c << 4;
}

/*
return the first 4 bit, the last 4 bit are set to 0
*/
char get_left(char c)
{
	return c & 15;
}

/*
move the last 4 bit to the left
the new last 4 bit are set to 0
*/
char get_right(char c)
{
	c = c >> 4;
	return c & 15;
}

/*
insert the first 4 bit of piece into the first 4 bit of tuple
*/
void insert_left(char piece, char *tuple)
{
	char eraser = 240;				// = 00001111
	*tuple = *tuple & eraser; // første 4 bit satt til 0
	*tuple = *tuple | piece;	// sett inn brikken
}

/*
insert the last 4 bit of piece into the last 4 bit of tuple
*/
void insert_right(char piece, char *tuple)
{
	char eraser = 15;
	*tuple = *tuple & eraser; // siste 4 bit satt til 0
	piece = move_right(piece);
	*tuple = *tuple | piece; // sett inn brikken
}

/*
determine if a piece is Black
*/
int is_black(char piece)
{
	return piece & 1;
}

/*
Determine if a piece is a pawn
*/
