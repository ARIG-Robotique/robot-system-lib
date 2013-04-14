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
 * Le configuration de l'IO est fait en mme temps.
 */
void Board2007NoMux::setPinForCapteur(char capteurId, char pin) {
	setPinForCapteur(capteurId, pin, false);
}

void Board2007NoMux::setPinForCapteur(char capteurId, char pin, boolean reverse) {
	if (check(capteurId)) {
		pinMode(pin, INPUT);
		capteurPins[capteurId] = pin;
		capteurReverse[capteurId] = reverse;

		Serial.print(" * Configuration capteur ");
		Serial.print(capteurId, DEC);
		Serial.print(" sur la pin ");
		Serial.println(pin, DEC);
	}
}

/*
 * Fonction de lecture de la valeur d'un capteur.
 * La rŽcupŽration se fait par l'ID du capteur.
 */
char Board2007NoMux::readCapteurValue(char capteurId) {
	if (check(capteurId) && capteurPins[capteurId] != UNDEF_PIN) {
		int val = digitalRead(capteurPins[capteurId]);
		if (capteurReverse[capteurId] == true) {
			val = !val;
		}
		return val;
	}

	return UNDEF_VAL;
}

/*
 * Contr™le que l'ID du capteur est bien dans les bornes pour eviter
 * une erreur de lecture du tableau des pin des capteurs
 */
boolean Board2007NoMux::check(char capteurId) {
	if (capteurId >= 0 && capteurId < NB_CAPTEUR) {
		return true;
	}

	return false;
}
