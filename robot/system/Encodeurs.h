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
	void setCoefs(double coefGauche, double coefDroit);

	void reset();

protected:
	double distance, orientation;

private:
	// Addresses cartes
	#define ADD_CARTE_CODEUR_DROIT  0xB0
	#define ADD_CARTE_CODEUR_GAUCHE 0xB2

	double coefGauche;
	double coefDroit;

	void setValeursCodeurs(double gauche, double droit);
	double lectureGauche();
	double lectureDroit();
	int lectureData(int address);

	byte retCode;
};

#endif /* ENCODEURS_H_ */
