/*
 * Encodeurs.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ENCODEURS_H_
#define ENCODEURS_H_

#include <Arduino.h>
#include "../utils/I2CUtils.h"

class Encodeurs {
public:
	Encodeurs();

	void printVersion();
	void lectureValeurs();
	double getDistance();
	double getOrientation();

	void setValeursCodeurs(double gauche, double droit);
	void reset();

protected:
	double distance, orientation;

private:
	#define CMD_RESET	'r'
	#define CMD_LECTURE 'l'
	#define	CMD_VERSION	'v'

	#define ADD_CARTE_CODEUR_DROIT  0xB0
	#define ADD_CARTE_CODEUR_GAUCHE 0xB2

	bool alternate;

	double lectureGauche();
	double lectureDroit();
	double lectureData(int address);

	byte retCode;
};

#endif /* ENCODEURS_H_ */
