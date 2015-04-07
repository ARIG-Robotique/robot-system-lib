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

class ARIGEncodeurs : public AbstractEncodeurs {
public:
	ARIGEncodeurs(byte addressGauche, byte addressDroit);
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
	int lectureData(int address);

	byte addressDroit;
	byte addressGauche;
};

#endif /* ARIG_ENCODEURS_H_ */
