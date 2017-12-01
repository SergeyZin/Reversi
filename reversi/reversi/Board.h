#pragma once
#include <map>
#include <iostream>

const std::map<char, int> LETTERS = { { 'A', 0 }, { 'B', 1 }, { 'C', 2 }, { 'D', 3 },
									  { 'E', 4 }, { 'F', 5 }, { 'G', 6 }, { 'H', 7 } };

enum Marker { WHITE = 'W', BLACK = 'B', EMPTY = '+', POSSIBLE = 'o' };

class Board {
public:
	char field[64];
	static const int size = 8;

	Board();
	Board(const Board &board);

	~Board();
	
	static int StepToIndex(char row, int col);
	
};

