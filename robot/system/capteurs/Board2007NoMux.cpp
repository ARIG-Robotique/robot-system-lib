/*
 * Board2007NoMux.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#include "Board2007NoMux.h"

Board2007NoMux::Board2007NoMux() {
}

void Board2007NoMux::setPinForCapteur(char capteurId, char pin) {
	if (check(capteurId)) {
		pinMode(pin, INPUT);
		this->capteurPins[capteurId] = pin;
	}
}

char Board2007NoMux::readCapteurValue(char capteurId) {
	if (check(capteurId)) {
		return digitalRead(this->capteurPins[capteurId]);
	}

	return -1;
}

boolean Board2007NoMux::check(char capteurId) {
	if (capteurId >= 0 && capteurId <= 24) {
		return true;
	}

	return false;
}
