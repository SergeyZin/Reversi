#include "Game.h"
#include <conio.h>
#include <stdlib.h>

Game::Game()
{
	board = Board();
	board.field[27] = WHITE;
	board.field[28] = BLACK;
	board.field[35] = BLACK;
	board.field[36] = WHITE;
}

Game::~Game()
{

}

void Game::Run() {
	system("cls");
	std::cout << "CHOOSE WHO GOES FIRST \n";
	std::cout << "If the person - PRESS 1 \n";
	std::cout << "If the computer - PRESS 2 \n";

	bool isChosen = false;
	int whoIsFirst;

	while (!isChosen) {
		std::cout << "> ";
		std::cin >> whoIsFirst;
		switch (whoIsFirst) {
		case 1: whoGoes = WHITE; isChosen = true; break;
		case 2: whoGoes = BLACK; isChosen = true; break;
		default:
			std::cout << "Incorrect input. Try again.\n";
			break;
		}
	}

	char row;
	int col;
	while (!IsTheEnd()) {
		DrawBoard();
		if (whoGoes == WHITE) {
			std::cout << "Human goes...\n> ";
			std::cin >> row >> col;
			if (firstPlayer.MakeMove(board, Board::StepToIndex(row, col)))
				whoGoes = BLACK;
			else std::cout << "Incorrect input. Try again.\n";
		}
		else if (whoGoes == BLACK) {
			std::cout << "Computer goes...\n";
			secondPlayer.MakeSmartMove(board);
			whoGoes = WHITE;
		}
	}
}

void Game::DrawBoard() {
	int n = board.size * board.size;
	char letters[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	int k = 0;
	for (int i = 0; i < board.size; ++i)
		std::cout << "   " << i + 1;
	std::cout << '\n' << "  ";
	for (int i = 0; i < board.size; ++i)
		std::cout << "____";
	for (int i = 0; i < n; ++i) {
		if (i % board.size == 0) {
			std::cout << '\n' << letters[i / board.size] << "| ";
		}
		std::cout << board.field[i] << "   ";
	}
	std::cout << std::endl;
}

bool Game::IsTheEnd() {
	int n = board.size * board.size;
	if (firstPlayer.score + secondPlayer.score == n)
		return true;
	return false;
}