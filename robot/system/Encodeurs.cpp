/*
 * Encodeurs.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "Encodeurs.h"
#include <Wire.h>

Encodeurs::Encodeurs() {
	alternate = false;
	distance = orientation = 0;
}

Encodeurs::~Encodeurs() {
}

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

double Encodeurs::lectureGauche() {
	return lectureData(ADD_CARTE_CODEUR_GAUCHE);
}
double Encodeurs::lectureDroit() {
	return lectureData(ADD_CARTE_CODEUR_DROIT);
}

double Encodeurs::lectureData(int address) {
	// 1. Envoi de la commande de lecture
	Wire.beginTransmission(address);
	Wire.write(CMD_LECTURE);
	Wire.endTransmission();

	// 2. Demande des infos sur 4 octet
	double value = 0;
	Wire.requestFrom(address, 4);
	while(Wire.available()) {
	    value += Wire.read();
	    value = value << 8;
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
