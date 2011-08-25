/*
 * Connect4.h
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#ifndef CONNECT4_H_
#define CONNECT4_H_

#define NB_ROWS 6
#define NB_COLUMNS 7

#include <iostream>
#include <iomanip>

#include "Threat.h"

using namespace std;

class Connect4 {
public:
	Connect4();
	virtual ~Connect4();

	void startGame();
	void setDifficulty(int difficulty);
	int evalBoard();

	int getTileNumber(int row, int column);
	int getBoard(int row, int col);
	void setBoard(int row, int col, int value);

	void playAtColumn(int col);
	void unplayAtColumn(int column);

	int firstEmptyRowAtColumn(int column);
	int lastFilledRowAtColumn(int column);

	int staticEvalBoard();
	int* possible();
	void computerPlay();

	int op(int x);
	int abPruning(int alpha, int beta, int depht);
	void threat(int s1, int s2, int *t11, int *t12, int *t13, int *t14, int *t21, int *t22, int *t23, int *t24);

	void displayBoard();
	void displayThreats();

private:
	//int board[NB_ROWS][NB_COLUMNS];
	int **board;
	int player;
	int gameFinished;
	int numberOfTilesOnBoard;
	int difficulty;
	string firstPlayer;
	ThreatCollection *threatCollection;
};

#endif /* CONNECT4_H_ */
