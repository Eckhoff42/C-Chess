
char turn_black(char c)
{
	return c | 1;
}

char turn_white(char c)
{
	return c & 254;
}

char move_right(char c)
{
	return c << 4;
}

char get_left(char c)
{
	return c & 15;
}

char get_right(char c)
{
	c = c >> 4;
	return c & 15;
}

void insert_left(char piece, char *tuple)
{
	char eraser = 240;				// = 00001111
	*tuple = *tuple & eraser; // første 4 bit satt til 0
	*tuple = *tuple | piece;	// sett inn brikken
}

void insert_right(char piece, char *tuple)
{
	char eraser = 15;
	*tuple = *tuple & eraser; // siste 4 bit satt til 0
	piece = move_right(piece);
	*tuple = *tuple | piece; // sett inn brikken
}

int valid_move(char *piece, char *to)
{
	return -1;
}