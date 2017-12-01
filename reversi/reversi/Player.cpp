#include "Player.h"

Player::Player() {
	score = 2;
	color = WHITE;
}


Player::~Player()
{
}

bool Player::MakeMove(Board &board, int ind) {
	if (ind != -1 && FindPossibleSteps(board)) {
		auto step = possibleSteps.find(ind);
		if (step != possibleSteps.end()) {
			board.field[ind] = color;
			Flip(board, ind);
			possibleSteps.clear();
			return true;
		}
	}
	return false;
}

bool Player::FindPossibleSteps(Board &board) {
	std::vector<int> square;
	int count = 0;
	for (int i = 0; i < board.size * board.size; ++i)
		if (board.field[i] != (char)EMPTY)
			square.push_back(i);

	for (int ind : square) {
		if (board.field[ind] == (char)color) {
			count += CheckDirections(board, ind);
		}
	}
	if (count > 0)
		return true;
	else return false;
}

int Player::CheckDirections(Board &board, int ind)
{
	int count = 0;
	for (int dir : directions) {
		int tind = ind;
		tind += dir;
		if (board.field[tind] == (char)EMPTY)
			continue;
		while (tind >= 0 && tind < board.size * board.size) {
			if (board.field[tind] != (char)color && board.field[tind] != (char)EMPTY)
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

void Player::Flip(Board &board, int ind)
{
	for (auto dir : possibleSteps[ind]) {
		int tind = ind + dir;
		while (board.field[tind] != (char)color) {
			board.field[tind] = color;
			tind += dir;
		}
	}
}

