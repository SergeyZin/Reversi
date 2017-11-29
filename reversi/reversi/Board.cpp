#include "Board.h"



Board::Board()
{
	for (int i = 0; i < size * size; ++i)
		Board::field[i] = EMPTY;
}


Board::~Board()
{
}
