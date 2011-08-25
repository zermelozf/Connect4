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
	// TODO Auto-generated destructor stub
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

int Connect4::evalBoard() {
    for (int i=0; i<NB_ROWS; i++) {
        for (int j=0; j<NB_COLUMNS; j++)
        {
            if (j+3<7)
            {
                if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3] && board[i][j] != 0) return board[i][j];
            }
            if (j+3<7 && i+3<6)
            {
                if (board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2] && board[i+2][j+2] == board[i+3][j+3] && board[i][j] != 0) return board[i][j];
            }
            if (i+3<6)
            {
                if (board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j] && board[i][j] != 0)
                    {return board[i][j];}
            }
            if (j>=3 && i+3<6)
            {
                if (board[i][j] == board[i+1][j-1] && board[i+1][j-1] == board[i+2][j-2] && board[i+2][j-2] == board[i+3][j-3] && board[i][j] != 0) return board[i][j];
            }
        }
    }
    if (numberOfTilesOnBoard == NB_ROWS*NB_COLUMNS) return 3;
    else return 0;
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
	int s1, s2;
	int t11 = 0, t12 = 0, t13 = 0, t14 = 0;
	int t21 = 0, t22 = 0, t23 = 0, t24 = 0;
	for (int i=0; i<NB_ROWS; i++) {
		for (int j=0; j<NB_COLUMNS; j++) {
			if (j+3<NB_COLUMNS) {
				s1 = op(board[i][j])+op(board[i][j+1])+op(board[i][j+2])+op(board[i][j+3]);
				s2 = op(-board[i][j])+op(-board[i][j+1])+op(-board[i][j+2])+op(-board[i][j+3]);
				threat(s1, s2, &t11, &t12, &t13, &t14, &t21, &t22, &t23, &t24);
			}
			if (j+3<NB_COLUMNS && i+3<NB_ROWS) {
				s1 = op(board[i][j])+op(board[i+1][j+1])+op(board[i+2][j+2])+op(board[i+3][j+3]);
				s2 = op(-board[i][j])+op(-board[i+1][j+1])+op(-board[i+2][j+2])+op(-board[i+3][j+3]);
				threat(s1, s2, &t11, &t12, &t13, &t14, &t21, &t22, &t23, &t24);			}
			if (i+3<NB_ROWS) {
				s1 = op(board[i][j])+op(board[i+1][j])+op(board[i+2][j])+op(board[i+3][j]);
				s2 = op(-board[i][j])+op(-board[i+1][j])+op(-board[i+2][j])+op(-board[i+3][j]);
				threat(s1, s2, &t11, &t12, &t13, &t14, &t21, &t22, &t23, &t24);			}
			if (j>=3 && i+3<NB_ROWS) {
				s1 = op(board[i][j])+op(board[i+1][j-1])+op(board[i+2][j-2])+op(board[i+3][j-3]);
				s2 = op(-board[i][j])+op(-board[i+1][j-1])+op(-board[i+2][j-2])+op(-board[i+3][j-3]);
				threat(s1, s2, &t11, &t12, &t13, &t14, &t21, &t22, &t23, &t24);			}
		}
	}
	int v1 = 15000*t14 + 2500*t13 + 50*t12 + t11;
	int v2 = 15000*t24 + 2500*t23 + 50*t22 + t21;
	return v1-v2;
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
	cout << "played" << endl;
	//threatCollection->display();
}

int Connect4::abPruning(int alpha, int beta, int depht) {
	if (depht == 1 || evalBoard() == 1 || evalBoard() == -1) {
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

int Connect4::op(int x) {
	if (x>0) return x;
	else return 0;
}


void Connect4::threat(int s1, int s2, int *t11, int *t12, int *t13, int *t14, int *t21, int *t22, int *t23, int *t24) {
	if (s1==1 && s2 ==0) {(*t11)++;}
	if (s1==2 && s2 ==0) {(*t12)++;}
	if (s1==3 && s2 ==0) {(*t13)++;}
	if (s1==4 && s2 ==0) {(*t14)++;}
	if (s1==0 && s2 ==1) {(*t21)++;}
	if (s1==0 && s2 ==2) {(*t22)++;}
	if (s1==0 && s2 ==3) {(*t23)++;}
	if (s1==0 && s2 ==4) {(*t24)++;}
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
