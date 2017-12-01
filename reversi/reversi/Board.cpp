#include "Board.h"



Board::Board()
{
	for (int i = 0; i < size * size; ++i)
		Board::field[i] = EMPTY;
}

Board::Board(const Board & board) {
	memcpy(this->field, board.field, sizeof(field));
}


Board::~Board()
{
}

int Board::StepToIndex(char row, int col)
{
	row = toupper(row);
	auto it = LETTERS.find(row);
	if (it != LETTERS.end() && col >= 1 && col <= 8) {
		int ind = it->second * Board::size + col - 1;
		return ind;
	}
	else return -1;
}
