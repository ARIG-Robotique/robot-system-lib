/*
 * Encodeurs.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ENCODEURS_H_
#define ENCODEURS_H_

#include <Arduino.h>
#include "../../common.h"
#include "../utils/I2CUtils.h"

class Encodeurs {
public:
	Encodeurs();

	void lectureValeurs();
	double getDistance();
	double getOrientation();

	void setValeursCodeurs(int gauche, int droit);
	void reset();

#ifdef DEBUG_MODE
	void printVersion();
#endif

protected:
	double distance, orientation;

private:
	// Command I2C
	#define CMD_RESET		'r'
	#define CMD_LECTURE 	'l'
	#define CMD_SETUP		's'
	#define	CMD_VERSION		'v'

	// Paramètre de configuration
	#define PARAM_INVERT 	'I'

	// Addresses cartes
	#define ADD_CARTE_CODEUR_DROIT  0xB0
	#define ADD_CARTE_CODEUR_GAUCHE 0xB2

	bool alternate;

	int lectureGauche();
	int lectureDroit();
	int lectureData(int address);

	byte retCode;
};

#endif /* ENCODEURS_H_ */
