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
ARIGEncodeurs::ARIGEncodeurs() {
	distance = orientation = 0;
	retCode = I2C_ACK;
	coefGauche = 1.0;
	coefDroit = 1.0;
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
 * Définition des coeficient pour l'ajustement des valeur codeur.
 * Cela permet de compenser le défaut éventuel d'une roue codeuse par rapport a l'autre.
 */
void ARIGEncodeurs::setCoefs(double coefGauche, double coefDroit) {
	this->coefGauche = coefGauche;
	this->coefDroit = coefDroit;
}

/*
 * Lecture de la valeurs des codeurs.
 * La lecture est alterné afin de ne pas inclure d'erreur du au temps de lecture.
 */
void ARIGEncodeurs::lectureValeurs() {
	double gauche = lectureGauche();
	double droit = lectureDroit();
	setValeursCodeurs(gauche, droit);

#ifdef DEBUG_MODE
	Serial.print(gauche);
	Serial.print(";");Serial.print(droit);
#endif
}

/*
 * Lecture de la valeur du codeur de la roue gauche
 */
double ARIGEncodeurs::lectureGauche() {
	return lectureData(ADD_CARTE_CODEUR_GAUCHE) * coefGauche;
}

/*
 * Lecture de la valeur du codeur de la roue droite
 */
double ARIGEncodeurs::lectureDroit() {
	return lectureData(ADD_CARTE_CODEUR_DROIT) * coefDroit;
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

double ARIGEncodeurs::getDistance() {
	return distance;
}

double ARIGEncodeurs::getOrientation() {
	return orientation;
}

void ARIGEncodeurs::setValeursCodeurs(double gauche, double droit) {
	distance = (droit + gauche) / 2.0;
	orientation = droit - gauche;
}
