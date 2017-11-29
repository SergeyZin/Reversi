#include "AIPlayer.h"
#include <stdlib.h>
#include <time.h>


AIPlayer::AIPlayer()
{
}

AIPlayer::AIPlayer(Marker c) : Player(c) {}


AIPlayer::~AIPlayer()
{
}

bool AIPlayer::MakeRandomMove(Board & board)
{
	if (FindPossibleSteps(board)) {
		std::vector<int> stepIndices;
		for (auto step : possibleSteps)
			stepIndices.push_back(step.first);

		srand(time(NULL));
		int randInd = rand() % stepIndices.size();

		board.field[stepIndices[randInd]] = color;
		Flip(board, stepIndices[randInd]);
		possibleSteps.clear();
		return true;
	}
	return false;
}

bool AIPlayer::FindPossibleSteps(Board & board) {
	std::vector<int> square;
	int count = 0;
	for (int i = 0; i < board.size * board.size; ++i)
		if (board.field[i] != EMPTY)
			square.push_back(i);

	for (int ind : square) {
		if (board.field[ind] == color) {
			count += CheckDirections(board, ind);
		}
	}
	if (count > 0)
		return true;
	else return false;
}

int AIPlayer::CheckDirections(Board & board, int ind)
{
	int count = 0;
	for (int dir : directions) {
		int tind = ind;
		tind += dir;
		if (board.field[tind] == EMPTY)
			continue;
		while (tind >= 0 && tind < board.size * board.size) {
			if (board.field[tind] == WHITE)
				tind += dir;
			else if (board.field[tind] == EMPTY) {
				count++;
				possibleSteps[tind].push_back(-dir);
				break;
			}
			else break;
		}
	}
	return count;
}

void AIPlayer::Flip(Board & board, int ind)
{
	for (auto dir : possibleSteps[ind]) {
		int tind = ind + dir;
		while (board.field[tind] != color) {
			board.field[tind] = color;
			tind += dir;
		}
	}
}
