/*
 * ARIGEncodeurs.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "ARIGEncodeurs.h"

#include <Wire.h>

/*
 * Constructeur
 */
ARIGEncodeurs::ARIGEncodeurs() : AbstractEncodeurs() {
	retCode = I2C_ACK;
}

ARIGEncodeurs::~ARIGEncodeurs() {
}

/*
 * Reset des valeurs codeurs
 */
void ARIGEncodeurs::reset() {
#ifdef DEBUG_MODE
	Serial.println(" * Reset carte codeur droit");
#endif
	lectureDroit();

#ifdef DEBUG_MODE
	Serial.println(" * Reset carte codeur gauche");
#endif
	lectureGauche();
}

/*
 * Lecture de la valeur du codeur de la roue gauche
 */
double ARIGEncodeurs::lectureGauche() {
	return lectureData(ADD_CARTE_CODEUR_GAUCHE);
}

/*
 * Lecture de la valeur du codeur de la roue droite
 */
double ARIGEncodeurs::lectureDroit() {
	return lectureData(ADD_CARTE_CODEUR_DROIT);
}

/*
 * Fonction de lecture depuis une des carte codeurs.
 * 1) On envoi la commande de lecture.
 * 2) On demande la récupération de 4 octets.
 */
int ARIGEncodeurs::lectureData(int address) {
	// Demande des infos sur 2 octets (int sur 2 byte avec un AVR 8 bits)
	int value = 0;
	Wire.requestFrom(address, 2);
	while(Wire.available()){
		value = value << 8;
		value += Wire.read();
	}

	return value;
}
