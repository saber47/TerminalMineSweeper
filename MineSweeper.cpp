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
	}
    return 0;
}

