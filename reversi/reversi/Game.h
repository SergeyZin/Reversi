#pragma once
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "AIPlayer.h"

class Game {
public:
	Board board;
	Marker whoGoes;
	Player firstPlayer;
	AIPlayer secondPlayer;

	Game();
	~Game();

	void Init();

	void Run();

	void Stop();

	void DrawBoard();

	//void MarkPossibleSteps()

	bool IsTheEnd();
};

