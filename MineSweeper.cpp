// MineSweeper.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <iostream>
#include <string>
#include <climits>
#include "GameStart.h"
using namespace std;


int main()
{
	while (true) {
		Game game;
		game.Play();
		cout << endl;
		/*
		cout << "Play again? [y/n]";
		string in;
		while (true) {
			getline(cin, in);
			if (in == "y") break;
			if (in == "n") exit(EXIT_SUCCESS);
			cout << "Please enter 'y' or 'n':\n";
		}
		*/
	}
    return 0;
}

