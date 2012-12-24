/*
 * Encodeurs.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "Encodeurs.h"

double distance;
double orientation;

Encodeurs::Encodeurs() {
	distance = orientation = 0;
}

Encodeurs::~Encodeurs() {
}

void Encodeurs::lectureValeurs() {
	// TODO : Interroger les cartes de lecture codeurs
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
