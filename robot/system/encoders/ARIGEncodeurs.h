/*
 * ARIGEncodeurs.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ARIG_ENCODEURS_H_
#define ARIG_ENCODEURS_H_

#include <Arduino.h>
#include <Wire.h>
#include "../../../utils/I2CUtils.h"
#include "../../../common.h"

class ARIGEncodeurs {
public:
	ARIGEncodeurs();

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

#endif /* ARIG_ENCODEURS_H_ */
