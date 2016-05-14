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
#include "../../../common.h"
#include "Board2007Define.h"

class Board2007NoMux {
public:
	Board2007NoMux();

	void setPinForCapteur(byte capteurId, byte pin);
	void setPinForCapteur(byte capteurId, byte pin, boolean reverse);
	void setPinForCapteur(byte capteurId, byte pin, boolean reverse, boolean pullUp);
	boolean readCapteurValue(byte capteurId);

private:
	char capteurPins[NB_CAPTEUR];
	boolean capteurReverse[NB_CAPTEUR];

	boolean check(byte capteurId);
};

#endif /* BOARD2007NOMUX_H_ */
