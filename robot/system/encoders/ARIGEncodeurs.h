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
#include "AbstractEncodeurs.h"
#include "../../../common.h"
#include "../../../utils/I2CUtils.h"

class ARIGEncodeurs : public AbstractEncodeurs {
public:
	ARIGEncodeurs();
	virtual ~ARIGEncodeurs();

	// -------------------------------------- //
	// Implémentation des méthodes abstraites //
	// -------------------------------------- //
	virtual void reset();

protected:

	// -------------------------------------- //
	// Implémentation des méthodes abstraites //
	// -------------------------------------- //
	virtual double lectureGauche();
	virtual double lectureDroit();

private:
	// TODO : Externalisé addresses cartes
	#define ADD_CARTE_CODEUR_DROIT  0xB0
	#define ADD_CARTE_CODEUR_GAUCHE 0xB2

	int lectureData(int address);

	byte retCode;
};

#endif /* ARIG_ENCODEURS_H_ */
