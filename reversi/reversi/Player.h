#pragma once
#include <vector>
#include <iostream>
#include "Board.h"

class Player {

protected:
	int directions[8] = { -8, -7, 1, 9, 8, 7, -1, -9 };
	std::map<int, std::vector<int>> possibleSteps;

public:
	
	Marker color;
	int score;

	Player();
	Player(Marker c);
	~Player();

	bool MakeMove(Board & board, char row, int col);
	bool FindPossibleSteps(Board & board);
	int CheckDirections(Board & board, int ind);
	void Flip(Board & board, int ind);
};

