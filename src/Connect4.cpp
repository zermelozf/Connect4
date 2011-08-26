/*
 * Connect4.cpp
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#include "Connect4.h"

#define MAX(a,b) (a>=b?a:b)
#define MIN(a,b) (a<=b?a:b)

Connect4::Connect4() {
	board = new int* [NB_ROWS];
		for (int i=0; i<NB_ROWS; i++) {
			board[i] = new int [NB_COLUMNS];
		}
	startGame();
	threatCollection = new ThreatCollection(board, NB_ROWS, NB_COLUMNS);
	//threatCollection->display();
}

Connect4::~Connect4() {
	for (int i=0; i<NB_ROWS; i++) {
		delete [] board[i];
	}
	delete board;
	delete threatCollection;
}

void Connect4::startGame() {
	for (int i=0; i<NB_ROWS; i++) {
		for (int j=0; j<NB_COLUMNS; j++) {
			board[i][j] = 0;
		}
	}
	player = 1;
	gameFinished = 0;
	numberOfTilesOnBoard = 0;
	//threatCollection->display();
}

void Connect4::setDifficulty(int dif) {
	difficulty = dif;
}

bool Connect4::isGameFinished() {
	return threatCollection->hasFourInARow();
}

int Connect4::getTileNumber(int row, int col) {
	return (NB_ROWS-row)*NB_COLUMNS+col;
}

int Connect4::getBoard(int row, int col) {
	return board[row][col];
}

void Connect4::setBoard(int row, int col, int value) {
	board[row][col] = value;
}

void Connect4::playAtColumn(int col) {
	int row = firstEmptyRowAtColumn(col);
	if (row != -1) {
		board[row][col] = player;
		player = -player;
		numberOfTilesOnBoard++;
	}
}

void Connect4::unplayAtColumn(int col) {
	int row = lastFilledRowAtColumn(col);
	board[row][col] = 0;
	player = -player;
	numberOfTilesOnBoard--;
}

int Connect4::firstEmptyRowAtColumn(int col) {
	for (int i=0; i<NB_ROWS; i++) {
		if (getBoard(i, col) == 0)
			return i;
	}
	return -1;
}

int Connect4::lastFilledRowAtColumn(int col) {
	int last = 0;
	for (int i=0; i<NB_ROWS; i++) {
		if (getBoard(i, col) != 0)
			last = i;
	}
	return last;
}

int Connect4::staticEvalBoard() {
	return threatCollection->eval();
}

int* Connect4::possible() {
	int *pMoves = (int*)malloc(NB_COLUMNS*sizeof(int));
	for (int j=0; j<NB_COLUMNS; j++) {
		pMoves[j] = -1;
		if (firstEmptyRowAtColumn(j) != -1) {
			pMoves[j] = 1;
		}
	}
	return pMoves;
}

void Connect4::computerPlay() {
	int score, bestMove, bestScore;
	int nply = difficulty;
	int *pMoves = possible();

	printf("nply: %d \nScores :", nply);
	if (player == 1) {
		bestScore = -1000000000;
		for (int k=0; k<NB_COLUMNS; k++) {
			if (pMoves[k]==1) {
				playAtColumn(k);
				score = abPruning(1000000000, -1000000000, nply);
				printf("%d ", score);
				if ( score > bestScore) {
					bestScore = score;
					bestMove = k;
				}
				unplayAtColumn(k);
			}
		}
		printf("\n");
	}
	if (player == -1) {
		bestScore = 1000000000;
		for (int k=0; k<NB_COLUMNS; k++) {
			if (pMoves[k]==1) {
				playAtColumn(k);
				score = abPruning(1000000000, -1000000000, nply);
				printf("%d ", score);
				if ( score < bestScore) {
					bestScore = score;
					bestMove = k;
				}
				unplayAtColumn(k);
			}
		}
		printf("\n");
	}
	playAtColumn(bestMove);
}

int Connect4::abPruning(int alpha, int beta, int depht) {
	if (depht == 1 || isGameFinished() == true) {
		return staticEvalBoard();
	}
	int *pMoves = possible();
	if (player == -1) {
		for (int k=0; k<NB_COLUMNS; k++) {
			if (pMoves[k] == 1) {
				playAtColumn(k);
				alpha = MIN(alpha, abPruning(alpha, beta, depht-1));
				unplayAtColumn(k);
				if (alpha <= beta) {break;}
			}
		}
		return alpha;
	}
	else {
		for (int k=0; k<NB_COLUMNS; k++) {
			if (pMoves[k] == 1) {
				playAtColumn(k);
				beta = MAX(beta, abPruning(alpha, beta, depht-1));
				unplayAtColumn(k);
				if (alpha <= beta) {break;}
			}
		}
		return beta;
	}
}

void Connect4::displayBoard() {
	for (int i=0; i<NB_ROWS; i++) {
		for (int j=0; j<NB_COLUMNS; j++) {
			cout << setw(6) << "|    ";
		}
				cout << " |" << endl;
		for (int j=0; j<NB_COLUMNS; j++) {
			if (board[5-i][j] == 1)
				cout << setw(6) << "|  X ";
			else if (board[5-i][j] == -1)
				cout << setw(6) << "|  O ";
			else
				cout << setw(6) << "|    ";
		}
		cout << " |" << endl;
	}
}

void Connect4::displayThreats() {
	threatCollection->display();
}
