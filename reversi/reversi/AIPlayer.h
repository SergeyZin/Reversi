#pragma once

#include "Player.h"

class AIPlayer:	public Player {
private:
	const int POSITIONCOST[64] =												
	{
		 90,-60,10,10,10,10,-60,90,
		 -60,-80,5,5,5,5,-80,-60,
		 10,5,1,1,1,1,5,10, 
		 10,5,1,1,1,1,5,10,
		 10,5,1,1,1,1,5,10,
		 10,5,1,1,1,1,5,10,
		 -60,-80,5,5,5,5,-80,-60,
		 90,-60,10,10,10,10,-60,90 
	};

public:
	AIPlayer();
	~AIPlayer();

	bool MakeMove(Board &board, int ind, Marker playerColor);

	bool MakeRandomMove(Board &board);

	bool MakeSmartMove(Board &board);

	bool FindPossibleSteps(Board &board, Marker playerColor);

	int CheckDirections(Board &board, int ind, Marker playerColor);

	void Flip(Board &board, int ind, Marker playerColor);

	int Heuristic(Board &board);

	int EvaluateMoves(Board &board, int alpha, int beta, int depth, bool isMaximizing);

	std::vector<Board> GenerateChildren(Board &board, Marker playerColor);
};

