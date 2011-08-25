/*
 * main.cpp
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#include <iostream>
#include <cmath>

using namespace std;

#include "Connect4.h"

int main() {

	cout << "Begin" << endl;
	Connect4 game =  Connect4();
	game.setDifficulty(3);
	while(game.evalBoard() != 1 && game.evalBoard() != -1) {
		game.computerPlay();
		game.displayBoard();
		game.displayThreats();
		cout << endl;
	}
	return 0;
}


