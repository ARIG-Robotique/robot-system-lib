/*
 * Encodeurs.cpp
 *
 *  Created on: 22 d�c. 2012
 *      Author: mythril
 */

#include <Arduino.h>
#include <Wire.h>
#include "Encodeurs.h"

/*
 * Constructeur
 */
Encodeurs::Encodeurs() {
	alternate = false;
	distance = orientation = 0;
}

/*
 * Reset des valeurs codeurs
 */
void Encodeurs::reset() {
	Serial.println(" * Reset carte codeur droit");
	Wire.beginTransmission(ADD_CARTE_CODEUR_DROIT);
	Wire.write(CMD_RESET);
	Wire.endTransmission();

	Serial.println(" * Reset carte codeur gauche");
	Wire.beginTransmission(ADD_CARTE_CODEUR_GAUCHE);
	Wire.write(CMD_RESET);
	Wire.endTransmission();
}

/*
 * Lecture de la valeurs des codeurs.
 * La lecture est altern� afin de ne pas inclure d'erreur du au temps de lecture.
 */
void Encodeurs::lectureValeurs() {
	alternate = !alternate;
	double gauche, droit;
	if (alternate) {
		gauche = lectureGauche();
		droit = lectureDroit();
	} else {
		droit = lectureDroit();
		gauche = lectureGauche();
	}
	setValeursCodeurs(gauche, droit);
}

/*
 * Lecture de la valeur du codeur de la roue gauche
 */
double Encodeurs::lectureGauche() {
	return lectureData(ADD_CARTE_CODEUR_GAUCHE);
}

/*
 * Lecture de la valeur du codeur de la roue droite
 */
double Encodeurs::lectureDroit() {
	return lectureData(ADD_CARTE_CODEUR_DROIT);
}

/*
 * Fonction de lecture depuis une des carte codeurs.
 * 1) On envoi la commande de lecture.
 * 2) On demande la r�cup�ration de 4 octets.
 */
double Encodeurs::lectureData(int address) {
	// 1. Envoi de la commande de lecture
	Wire.beginTransmission(address);
	Wire.write(CMD_LECTURE);
	Wire.endTransmission();

	// 2. Demande des infos sur 2 octets (int sur 2 byte avec un AVR 8 bits)
	int value = 0;
	Wire.requestFrom(address, 2);
	while(Wire.available()) {
	    value += Wire.read();
	    value = value << 8; // D�calage a gauche. L'envoi est fait du MSB au LSB
	}

	return value;
}

double Encodeurs::getDistance() {
	return distance;
}

double Encodeurs::getOrientation() {
	return orientation;
}

void Encodeurs::setValeursCodeurs(double gauche, double droit) {
	distance = (droit + gauche) / 2;
	orientation = droit - gauche;
}
