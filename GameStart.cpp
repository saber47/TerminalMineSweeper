#include "GameStart.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <random>
#include <time.h>
#include <vector>

using namespace std;


void Game::Init() {
	srand(time(NULL));
	int n = mineN;
	while (n > 0) {
		int i = rand() % dimX;
		int j = rand() % dimY;
		if (data[i][j] != 9) {
			data[i][j] = 9;
			if (i > 0 && data[i - 1][j] != 9) data[i - 1][j]++;
			if (i < dimX - 1 && data[i + 1][j] != 9) data[i + 1][j]++;
			if (j > 0 && data[i][j - 1] != 9) data[i][j - 1]++;
			if (j < dimY - 1 && data[i][j + 1] != 9) data[i][j + 1]++;
			if (i > 0 && j > 0 && data[i - 1][j - 1] != 9) data[i - 1][j - 1]++;
			if (i > 0 && j < dimY-1 && data[i - 1][j + 1] != 9) data[i - 1][j + 1]++;
			if (i < dimX-1 && j > 0 && data[i + 1][j - 1] != 9) data[i + 1][j - 1]++;
			if (i < dimX-1 && j < dimY-1 && data[i + 1][j + 1] != 9) data[i + 1][j + 1]++;
			n--;
		}
	}
	return;
}

void Game::Quit() {
	cout << "Quiting game\n";
	exit(EXIT_SUCCESS);
	return;
}

Game::Game() {
	cout << "Welcome to play Mine Sweeper Console Version.\n";
	cout << "Please choose difficulty:\n";
	cout << "[E] - Easy: 8 Mines\n";
	cout << "[M] - Medium: 20 Mines\n";
	cout << "[H] - Hard: 40 Mines\n";
	cout << "[Q] - Quit game\n";
	cout << "[In]: ";
	bool loop = true;
	while (loop) {
		string in;
		getline(cin, in);
		switch (in[0]) {
		case 'e':
		case 'E':
			loop = false;
			mineN = 8;
			dimX = 8;
			dimY = 8;
			cout << "\nPlaying Easy mode\n";
			break;
		case 'm':
		case 'M':
			loop = false;
			mineN = 20;
			dimX = 12;
			dimY = 12;
			cout << "\nPlaying Medium mode\n";
			break;
		case 'h':
		case 'H':
			loop = false;
			mineN = 40;
			dimX = 16;
			dimY = 16;
			cout << "\nPlaying Hard mode\n";
			break;
		case 'q':
			cout << "Quiting game\n";
			Quit();
			return;
		default:
			cout << "\n";
			cout << "[E] - Easy: 5 Mines\n";
			cout << "[M] - Medium: 10 Mines\n";
			cout << "[H] - Hard: 20 Mines\n";
			cout << "[Q] - Quit game\n";
			cout << "\n[In]: ";
		}
	}
	board = vector<vector<string>>(dimX, vector<string>(dimY, "[ ]"));
	data = vector<vector<int>>(dimX, vector<int>(dimY, 0));
	Init();
	return;
}
void Game::PrintBoard() {
	int n = board[0].size();
	cout << "     ";
	for (int i = 0; i < n; i++) printf("%2d  ", i);
	cout << "\n";
	cout << "     ";
	for (int i = 0; i < n; i++) cout << "====";
	cout << "\b \n";
	int rowID = 0;
	for (auto &row : board) {
		printf("%2d ||", rowID);
		rowID++;
		for (auto &x:row) cout << x << " ";
		cout << "\b||\n";
	}
	cout << "     ";
	for (int i = 0; i < n; i++) cout << "====";
	cout << "\b \n";
}

void debug(vector<vector<int>> data) {
	for (auto &row : data) {
		for (auto &i : row) {
			[=]() {if (i == 9) cout << "M "; else  if (i == 0) cout << "  "; else cout << i << " "; }();
		}
		cout << endl;
	}
}

void Game::Lose() {
	cout << endl;
	cout << "Sorry you lost :(\n";
}

void Game::Win() {
	for (int i = 0; i < dimX; i++) {
		for (int j = 0; j < dimY; j++) {
			if (data[i][j] == 9) board[i][j][1] = '!';
		}
	}
	PrintBoard();
	cout << endl;
	cout << "Congrats! You WIN !\n";
}

void Game::Mark(int i, int j) {
	if (board[i][j][0] == ' ') return;
	switch (board[i][j][1]) {
	case ' ':
		board[i][j][1] = '!';
		break;
	case '!':
		board[i][j][1] = '?';
		break;
	case '?':
		board[i][j][1] = ' ';
		break;
	default:
		break;
	}
	return;
}

void Game::Flip(int i, int j) {
	if (data[i][j] == 0 && board[i][j][0]!=' ') {
		total--;
		board[i][j] = "   ";
	}
	else if (board[i][j][1] == ' ') {
		total--;
		board[i][j][1] = '0' + data[i][j];
	}
	if (i > 0 && data[i-1][j]==0 && board[i - 1][j] != "   ") Flip(i - 1, j);
	if (i < dimX - 1 && data[i+1][j] ==0 && board[i + 1][j] != "   ") Flip(i + 1, j);
	if (j > 0 && data[i][j-1] ==0 && board[i][j - 1] != "   ") Flip(i, j - 1);
	if (j < dimY - 1 && data[i][j + 1] == 0 && board[i][j + 1] != "   ") Flip(i, j + 1);
	if (i > 0 && j > 0 && data[i-1][j-1] == 0 && board[i - 1][j - 1] != "   ") Flip(i - 1, j - 1);
	if (i > 0 && j < dimY - 1 && data[i-1][j+1] == 0 && board[i - 1][j + 1] != "   ") Flip(i - 1, j + 1);
	if (i < dimX - 1 && j > 0 && data[i+1][j-1] == 0 && board[i + 1][j - 1] != "   ") Flip(i + 1, j - 1);
	if (i < dimX - 1 && j < dimY - 1 && data[i+1][j+1] == 0 && board[i + 1][j + 1] != "   ") Flip(i + 1, j + 1);
}

void Game::Play() {
	total = dimX*dimY;
	PrintBoard();
	while (total != mineN) {
		int i=0, j=0;
		char move = '\0';
		while (true) {
			debug(data);
			cout << "Total number of mines: " << mineN << endl;
			cout << "'r i j' -- reveal tile (i,j)\n";
			cout << "'f i j' -- Flag/clear tile (i,j)\n";
			cout << "'q' -- quit game\n";
			cout << "[In]: ";
			string instr;
			getline(cin, instr);
			istringstream iss(instr);
			if (!(iss >> move)) {
				PrintBoard();
				continue;
			}
			if (move != 'r' && move != 'f' && move != 'q') {
				PrintBoard();
				continue;
			}
			if (move == 'q') break;
			if (!(iss >> i >> j)) {
				PrintBoard();
				continue;
			}
			if (i < 0 || i >= dimX) {
				PrintBoard();
				continue;
			}
			if (j < 0 || j >= dimY) {
				PrintBoard();
				continue;
			}
			break;
		}
		int tile = data[i][j];
		if (move == 'r') {
			if (board[i][j][1] == '!' || board[i][j][1] == '?') {
				PrintBoard();
				printf("You flagged this tile: (%d,%d). Please unflag first\n", i, j);
				continue;
			}
			if (tile == 9) {
				board[i][j][1] = 'M';
				PrintBoard();
				Lose();
				return;
			}			
			else Flip(i, j);
		}
		else if (move == 'f') Mark(i, j);
		else Quit();
		PrintBoard();
	}
	return Win();
}