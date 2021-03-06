/*
 * Board2007NoMux.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#include "Board2007NoMux.h"

Board2007NoMux::Board2007NoMux() {
	// Initialisation
	for (int i = 0 ; i < NB_CAPTEUR ; i++) {
		capteurPins[i] = UNDEF_PIN;
		capteurReverse[i] = false;
	}
}

/*
 * Fonction permettant d'associer un idCapteur a un pin de la carte.
 * Le configuration de l'IO est fait en même temps.
 *
 * /!\ A appeler depuis la fonction setup().
 */
void Board2007NoMux::setPinForCapteur(byte capteurId, byte pin) {
	setPinForCapteur(capteurId, pin, false, false);
}

void Board2007NoMux::setPinForCapteur(byte capteurId, byte pin, boolean reverse) {
	setPinForCapteur(capteurId, pin, reverse, false);
}

void Board2007NoMux::setPinForCapteur(byte capteurId, byte pin, boolean reverse, boolean pullUp) {
	if (check(capteurId)) {
		pinMode(pin, (pullUp) ? INPUT_PULLUP : INPUT);
		capteurPins[capteurId] = pin;
		capteurReverse[capteurId] = reverse;

#ifdef DEBUG_MODE
		Serial.print(" * Configuration capteur ");
		Serial.print(capteurId, DEC);
		Serial.print(" sur la pin ");
		Serial.println(pin, DEC);
#endif
	}
}

/*
 * Fonction de lecture de la valeur d'un capteur.
 * La récupération se fait par l'ID du capteur.
 */
boolean Board2007NoMux::readCapteurValue(byte capteurId) {
	if (check(capteurId) && capteurPins[capteurId] != UNDEF_PIN) {
		int val = digitalRead(capteurPins[capteurId]);
		if (capteurReverse[capteurId] == true) {
			val = !val;
		}
		return val == HIGH;
	}

	return UNDEF_VAL;
}

/*
 * Contrôle que l'ID du capteur est bien dans les bornes pour eviter
 * une erreur de lecture du tableau des pins des capteurs
 */
boolean Board2007NoMux::check(byte capteurId) {
	if (capteurId >= 0 && capteurId < NB_CAPTEUR) {
		return true;
	}

	return false;
}
