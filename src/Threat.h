/*
 * Threat.h
 *
 *  Created on August 24, 2011
 *      Author: zermelozf
 */

#ifndef THREAT_H_
#define THREAT_H_

#include <iostream>
#include <iomanip>

#define NB_TILES_IN_THREAT 4

class Threat {
public:
	Threat(int *tile1, int *tile2, int *tile3, int *tile4);
	virtual ~Threat();

	int eval();
	bool isFourInARow();

	void display();
private:
	int **tile;
	int value;
};

class ThreatCollection {
public:
	ThreatCollection(int **board, int nb_rows, int nb_columns);
	virtual ~ThreatCollection();

	int eval();
	bool hasFourInARow();

	void display();

private:
	Threat *threat[200];
	int nb_threat;
	int nb_positive_threat;
	int nb_negative_threat;
};

#endif /* THREAT_H_ */
