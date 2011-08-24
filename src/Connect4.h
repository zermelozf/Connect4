/*
 * Connect4.h
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#ifndef CONNECT4_H_
#define CONNECT4_H_

#include <iostream>
#include <string>

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

	long int staticEvalBoard();
	int* possible();
	void computerPlay();

	long int abPruning(long int alpha, long int beta, int depht);
	int op(int x);
	void threat(int s1, int s2, int *t11, int *t12, int *t13, int *t14, int *t21, int *t22, int *t23, int *t24);

private:
	int board[6][7];
	int player;
	int gameFinished;
	int numberOfTilesOnBoard;
	int difficulty;
	string firstPlayer;
};

#endif /* CONNECT4_H_ */
