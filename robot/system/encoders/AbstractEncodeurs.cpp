/*
 * AbstractEncodeurs.cpp
 *
 *  Created on: 25 juin 2013
 *      Author: mythril
 */

#include "AbstractEncodeurs.h"
#include <Arduino.h>
#include "../../../common.h"

AbstractEncodeurs::AbstractEncodeurs() {
	distance = orientation = 0;
	coefGauche = 1.0;
	coefDroit = 1.0;
}

AbstractEncodeurs::~AbstractEncodeurs() {
}

/*
 * Définition des coeficient pour l'ajustement des valeur codeur.
 * Cela permet de compenser le défaut éventuel d'une roue codeuse par rapport a l'autre.
 */
void AbstractEncodeurs::setCoefs(double coefGauche, double coefDroit) {
	this->coefGauche = coefGauche;
	this->coefDroit = coefDroit;
}

/*
 * Lecture de la valeurs des codeurs.
 * La lecture est alterné afin de ne pas inclure d'erreur du au temps de lecture.
 */
void AbstractEncodeurs::lectureValeurs() {
	double gauche = lectureGauche() * coefGauche;
	double droit = lectureDroit() * coefDroit;
	setValeursCodeurs(gauche, droit);

#ifdef LIB_DEBUG_MODE
	Serial.print(gauche);
	Serial.print(";");Serial.print(droit);
#endif
}

double AbstractEncodeurs::getDistance() {
	return distance;
}

double AbstractEncodeurs::getOrientation() {
	return orientation;
}

void AbstractEncodeurs::setValeursCodeurs(double gauche, double droit) {
	distance = (droit + gauche) / 2.0;
	orientation = droit - gauche;
}
