#pragma once

#include "Player.h"

class AIPlayer:	public Player {
public:
	AIPlayer();
	AIPlayer(Marker c);
	~AIPlayer();

	bool MakeRandomMove(Board & board);
	bool FindPossibleSteps(Board & board);
	int CheckDirections(Board & board, int ind);
	void Flip(Board & board, int ind);
};

