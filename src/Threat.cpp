/*
 * Threat.cpp
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#include "Threat.h"

int op(int x) {
	if (x>0) return x;
	else return 0;
}

using namespace std;

Threat::Threat(int *tile0, int *tile1, int *tile2, int *tile3) {
	tile =  new int* [4];
	tile[0] = tile0;
	tile[1] = tile1;
	tile[2] = tile2;
	tile[3] = tile3;
}

int Threat::eval() {
	int s1 = op(*tile[0])+op(*tile[1])+op(*tile[2])+op(*tile[3]);
	int s2 = op(-*tile[0])+op(-*tile[1])+op(-*tile[2])+op(-*tile[3]);
	if (s1 == 0 && s2 != 0)
		return -s2;
	else if (s1 != 0 && s2 == 0)
		return s1;
	else return 0;
}

bool Threat::isFourInARow() {
	if (*tile[0] == *tile[1] && *tile[1] == *tile[2] && *tile[2] == *tile[3] && *tile[0] != 0)
		return true;
	return false;
}

Threat::~Threat() {

}

void Threat::display() {
	for (int i=0; i<NB_TILES_IN_THREAT; i++) {
		cout << setw(2) << *tile[i] << " ";
	}
	cout << "value: " << eval() << " is4inAR: " << isFourInARow() << endl;
}


ThreatCollection::ThreatCollection(int **board, int nb_rows, int nb_columns) {
	nb_threat = 0;
	for (int i=0; i<nb_rows; i++) {
	        for (int j=0; j<nb_columns; j++)
	        {
	            if (j+3<7) {
	            	threat[nb_threat] = new Threat(&board[i][j], &board[i][j+1], &board[i][j+2], &board[i][j+3]) ;
	            	nb_threat++;
	            }
	            if (j+3<7 && i+3<6) {
	                threat[nb_threat] = new Threat(&board[i][j], &board[i+1][j+1], &board[i+2][j+2], &board[i+3][j+3]);
	            	nb_threat++;
	        	}
	            if (i+3<6) {
	                threat[nb_threat] = new Threat(&board[i][j], &board[i+1][j], &board[i+2][j], &board[i+3][j]);
	                nb_threat++;
	            }
	            if (j>=3 && i+3<6) {
	                threat[nb_threat] = new Threat(&board[i][j], &board[i+1][j-1], &board[i+2][j-2], &board[i+3][j-3]);
	            	nb_threat++;
	            }
	        }
	    }
}

int ThreatCollection::eval() {
	int score = 0;
	for (int i=0; i<nb_threat; i++) {
		switch (threat[i]->eval()){
		case 0:
			break;
		case 1:
			score += 1;
			break;
		case 2:
			score += 50;
			break;
		case 3:
			score += 2500;
			break;
		case 4:
			score += 15000;
			break;
		case -1:
			score += -1;
			break;
		case -2:
			score += -50;
			break;
		case -3:
			score += -2500;
			break;
		case -4:
			score += -15000;
			break;
		default:
			break;
		}
	}
	return score;
}

bool ThreatCollection::hasFourInARow() {
	for (int i=0; i<nb_threat; i++) {
		if (threat[i]->isFourInARow())
			return true;
	}
	return false;
}

ThreatCollection::~ThreatCollection() {
	// TODO Auto-generated destructor stub
}

void ThreatCollection::display() {
	cout << "Display threats" << endl;
	cout << "nb_threat: " << this->nb_threat << endl;
	for (int i=0; i<nb_threat; i++) {
		threat[i]->display();
	}

}
