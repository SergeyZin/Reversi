#include "AIPlayer.h"
#include <stdlib.h>
#include <time.h>
#include <algorithm>

AIPlayer::AIPlayer()
{
	score = 2;
	color = BLACK;
}


AIPlayer::~AIPlayer(){}

bool AIPlayer::MakeMove(Board &board, int ind, Marker playerColor) {
	auto step = possibleSteps.find(ind);
	if (step != possibleSteps.end()) {
		board.field[ind] = playerColor;
		Flip(board, ind, playerColor);
		return true;
	}
	return false;
}


bool AIPlayer::MakeRandomMove(Board &board)
{
	if (FindPossibleSteps(board, color)) {
		std::vector<int> stepIndices;
		for (auto step : possibleSteps)
			stepIndices.push_back(step.first);

		srand(time(NULL));
		int randInd = rand() % stepIndices.size();

		board.field[stepIndices[randInd]] = color;
		Flip(board, stepIndices[randInd], color);
		possibleSteps.clear();
		return true;
	}
	return false;
}


bool AIPlayer::MakeSmartMove(Board &board) {
	std::vector<Board> children = GenerateChildren(board, color);
	if (children.size() > 0) {
		int maxHeuristic = INT_MIN;
		Board maxChild;
		for (auto child : children) {
			int h = EvaluateMoves(child, INT_MIN, INT_MAX, 4, false);
			if (h > maxHeuristic) {
				maxHeuristic = h;
				maxChild = child;
			}
		}
		board = maxChild;
		return true;
	}
	else return false;
}


int AIPlayer::EvaluateMoves(Board &board, int alpha, int beta, int depth, bool isMaximizing) {
	if (depth == 0)
		return Heuristic(board);

	if (isMaximizing) {
		int best = INT_MIN;
		for (auto child : GenerateChildren(board, BLACK)) {
			int val = EvaluateMoves(child, alpha, beta, depth - 1, false);
			best = std::max(best, val);
			alpha = std::max(alpha, best);

			if (beta <= alpha)
				break;
		}
		return best;
	}
	else {
		int best = INT_MAX;
		for (auto child : GenerateChildren(board, WHITE)) {
			int val = EvaluateMoves(child, alpha, beta, depth - 1, true);
			best = std::min(best, val);
			beta = std::min(beta, best);

			if (beta <= alpha)
				break;
		}
		return best;
	}
}


bool AIPlayer::FindPossibleSteps(Board &board, Marker playerColor) {
	std::vector<int> square;
	int count = 0;
	
	for (int i = 0; i < board.size * board.size; ++i)
		if (board.field[i] != (char)EMPTY)
			square.push_back(i);

	for (int ind : square) {
		if (board.field[ind] == (char)playerColor) {
			count += CheckDirections(board, ind, playerColor);
		}
	}

	if (count > 0)
		return true;
	
	else return false;
}


int AIPlayer::CheckDirections(Board &board, int ind, Marker playerColor)
{
	int count = 0;
	
	for (int dir : directions) {
		int tind = ind;
		tind += dir;
		
		if (board.field[tind] == (char)EMPTY)
			continue;
		
		while (tind >= 0 && tind < board.size * board.size) {
			if (board.field[tind] != (char)playerColor && board.field[tind] != (char)EMPTY)
				tind += dir;
		
			else if (board.field[tind] == (char)EMPTY) {
				count++;
				possibleSteps[tind].push_back(-dir);
				break;
			}
			else break;
		}
	}
	return count;
}


void AIPlayer::Flip(Board &board, int ind, Marker playerColor)
{
	for (auto dir : possibleSteps[ind]) {
		int tind = ind + dir;
	
		while (board.field[tind] != (char)playerColor) {
			board.field[tind] = playerColor;
			tind += dir;
		}
	}
}


int AIPlayer::Heuristic(Board &board)
{
	int h = 0;
	
	for (int i = 0; i < board.size * board.size; ++i) {
		if (board.field[i] == (char)color)
			h += POSITIONCOST[i];
		
		else if (board.field[i] != (char)EMPTY)
			h -= POSITIONCOST[i];
	}
	
	return h;
}


std::vector<Board> AIPlayer::GenerateChildren(Board &board, Marker playerColor)
{
	std::vector<Board> children;
	FindPossibleSteps(board, playerColor);
	for (auto step : possibleSteps) {
		Board newBoard = Board(board);
		MakeMove(newBoard, step.first, playerColor);
		children.push_back(newBoard);
	}
	possibleSteps.clear();
	return children;
}
