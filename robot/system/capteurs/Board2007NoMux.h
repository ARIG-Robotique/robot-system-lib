/*
 * Board2007NoMux.h
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 *
 * Gestion des capteurs de la carte de 2007 en accès direct (sans les MUX)
 */

#ifndef BOARD2007NOMUX_H_
#define BOARD2007NOMUX_H_

#include <Arduino.h>
#include "CapteurDefine.h"

class Board2007NoMux {
public:
	Board2007NoMux();

	void setPinForCapteur(unsigned char capteurId, char pin);
	void setPinForCapteur(unsigned char capteurId, char pin, boolean reverse);
	char readCapteurValue(unsigned char capteurId);

private:
	char capteurPins[NB_CAPTEUR];
	boolean capteurReverse[NB_CAPTEUR];

	boolean check(unsigned char capteurId);
};

#endif /* BOARD2007NOMUX_H_ */
