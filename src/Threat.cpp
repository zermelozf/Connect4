/*
 * Threat.cpp
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#include "Threat.h"

Threat::Threat(int *tile0, int *tile1, int *tile2, int *tile3) {
	tile =  new int* [4];
	tile[0] = tile0;
	tile[1] = tile1;
	tile[2] = tile2;
	tile[3] = tile3;
}

Threat::~Threat() {

}

void Threat::display() {
	std::cout << "In threat" << std::endl;
	for (int i=0; i<4; i++) {
		std::cout << "tile i" << tile[i] << " " <<std::endl;
	}
}


ThreatCollection::ThreatCollection(int **board, int nb_rows, int nb_columns) {
	nb_threat = 1;

	for (int i=0; i<nb_rows; i++) {
	        for (int j=0; j<nb_columns; j++)
	        {
	            if (j+3<7)
	            {
	            	if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3] && board[i][j] != 0) {
	            		threat[nb_threat-1] = new Threat(&board[i][j], &board[i][j+1], &board[i][j+2], &board[i][j+3]) ;
	            	}
	            }
	            if (j+3<7 && i+3<6)
	            {
	                if (board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2] && board[i+2][j+2] == board[i+3][j+3] && board[i][j] != 0)
	                	threat[nb_threat-1] = new Threat(&board[i][j], &board[i+1][j+1], &board[i+2][j+2], &board[i+3][j+3]);
	            }
	            if (i+3<6)
	            {
	                if (board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j] && board[i][j] != 0)
	                	threat[nb_threat-1] = new Threat(&board[i][j], &board[i+1][j], &board[i+2][j], &board[i+3][j]);
	            }
	            if (j>=3 && i+3<6)
	            {
	                if (board[i][j] == board[i+1][j-1] && board[i+1][j-1] == board[i+2][j-2] && board[i+2][j-2] == board[i+3][j-3] && board[i][j] != 0)
	                	threat[nb_threat-1] = new Threat(&board[i][j], &board[i+1][j-1], &board[i+2][j-2], &board[i+3][j-3]);
	            }
	        }
	    }
}

ThreatCollection::~ThreatCollection() {
	// TODO Auto-generated destructor stub
}

void ThreatCollection::display() {
	threat[0]->display();
}
