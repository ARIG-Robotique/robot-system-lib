/*
 * Encodeurs.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include <Arduino.h>
#include <Wire.h>

#include "Encodeurs.h"

#include "../../common.h"
#include "../utils/I2CUtils.h"

/*
 * Constructeur
 */
Encodeurs::Encodeurs() {
	alternate = false;
	distance = orientation = 0;
	retCode = I2C_ACK;
	coefGauche = 1.0;
	coefDroit = 1.0;
}

/*
 * Reset des valeurs codeurs
 */
void Encodeurs::reset() {
#ifdef DEBUG_MODE
	Serial.println(" * Reset carte codeur droit");
#endif
	Wire.beginTransmission(ADD_CARTE_CODEUR_DROIT);
	Wire.write(CMD_RESET);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		Serial.print(" * Carte codeur droit ");
		i2cUtils.printReturnCode(retCode);
	}
#endif

#ifdef DEBUG_MODE
	Serial.println(" * Reset carte codeur gauche");
#endif
	Wire.beginTransmission(ADD_CARTE_CODEUR_GAUCHE);
	Wire.write(CMD_RESET);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		Serial.print(" * Carte codeur gauche ");
		i2cUtils.printReturnCode(retCode);
	}
#endif
}

/*
 * Définition des coeficient pour l'ajustement des valeur codeur.
 * Cela permet de compenser le défaut éventuel d'une roue codeuse par rapport a l'autre.
 */
void Encodeurs::setCoefs(double coefGauche, double coefDroit) {
	this->coefGauche = coefGauche;
	this->coefDroit = coefDroit;
}

/*
 * Lecture de la valeurs des codeurs.
 * La lecture est alterné afin de ne pas inclure d'erreur du au temps de lecture.
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

#ifdef DEBUG_MODE
	Serial.print(gauche);
	Serial.print(";");Serial.print(droit);
#endif
}

/*
 * Lecture de la valeur du codeur de la roue gauche
 */
double Encodeurs::lectureGauche() {
	return lectureData(ADD_CARTE_CODEUR_GAUCHE) * coefGauche;
}

/*
 * Lecture de la valeur du codeur de la roue droite
 */
double Encodeurs::lectureDroit() {
	return lectureData(ADD_CARTE_CODEUR_DROIT) * coefDroit;
}

/*
 * Fonction de lecture depuis une des carte codeurs.
 * 1) On envoi la commande de lecture.
 * 2) On demande la récupération de 4 octets.
 */
int Encodeurs::lectureData(int address) {
	// 1. Envoi de la commande de lecture
	Wire.beginTransmission(address);
	Wire.write(CMD_LECTURE);
	retCode = Wire.endTransmission();
	if (i2cUtils.isError(retCode)) {
#ifdef DEBUG_MODE
		Serial.print(" * Lecture codeur ");
		Serial.print(address, HEX);
		i2cUtils.printReturnCode(retCode);
#endif
		return 0;
	} else {

		// 2. Demande des infos sur 2 octets (int sur 2 byte avec un AVR 8 bits)
		int value = 0;
		Wire.requestFrom(address, 2);
		while(Wire.available()){
			value = value << 8;
			value += Wire.read();
		}

		return value;
	}
}

double Encodeurs::getDistance() {
	return distance;
}

double Encodeurs::getOrientation() {
	return orientation;
}

void Encodeurs::setValeursCodeurs(double gauche, double droit) {
	distance = (droit + gauche) / 2.0;
	orientation = droit - gauche;
}

#ifdef DEBUG_MODE
/*
 * Cette méthode affiche la version de la carte sur la liaison série
 */
void Encodeurs::printVersion() {
	Wire.beginTransmission(ADD_CARTE_CODEUR_DROIT);
	Wire.write(CMD_VERSION);
	retCode = Wire.endTransmission();
	if (i2cUtils.isOk(retCode)) {
		Wire.requestFrom(ADD_CARTE_CODEUR_DROIT, 1);
		while(Wire.available() < 1);
		int software = Wire.read();

		Serial.print(" - Codeur droit [OK] (V : ");
		Serial.print(software);
		Serial.println(")");
	} else {
		Serial.println(" - Codeur droit [KO]");
		i2cUtils.printReturnCode(retCode);
	}

	Wire.beginTransmission(ADD_CARTE_CODEUR_GAUCHE);
	Wire.write(CMD_VERSION);
	retCode = Wire.endTransmission();
	if (i2cUtils.isOk(retCode)) {
		Wire.requestFrom(ADD_CARTE_CODEUR_GAUCHE, 1);
		while(Wire.available() < 1);
		int software = Wire.read();

		Serial.print(" - Codeur gauche [OK] (V : ");
		Serial.print(software);
		Serial.println(")");
	} else {
		Serial.println(" - Codeur gauche [KO]");
		i2cUtils.printReturnCode(retCode);
	}
}
#endif
