/*
 * Encodeurs.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "Encodeurs.h"
#include <Wire.h>

#define ADD_CARTE_CODEUR_DROIT 0x01;
#define ADD_CARTE_CODEUR_GAUCHE 0x02;

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
	// TODO : Interroger les cartes de lecture codeurs
	return 0;
}
double Encodeurs::lectureDroit() {
	// TODO : Interroger les cartes de lecture codeurs
	return 0;
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
