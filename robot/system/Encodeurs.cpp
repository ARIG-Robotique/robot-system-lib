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
		i2cUtils.printReturnCode(retCode);
	}
#endif
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
 * 2) On demande la récupération de 4 octets.
 */
double Encodeurs::lectureData(int address) {
	// 1. Envoi de la commande de lecture
	Wire.beginTransmission(address);
	Wire.write(CMD_LECTURE);
	retCode = Wire.endTransmission();
	if (i2cUtils.isError(retCode)) {
#ifdef DEBUG_MODE
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

#ifdef DEBUG_MODE
		Serial.print("Adresse : ");
		Serial.print(address, HEX);
		Serial.print(" -> ");
		Serial.println(value, DEC);
#endif
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
	distance = (droit + gauche) / 2;
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

/*
 * Configuration de l'inversion des valeurs codeurs
 */
void Encodeurs::configInvertCodeurs(boolean valG, boolean valD) {
	// Codeur Gauche
#ifdef DEBUG_MODE
	Serial.print(" * Configuration inversion codeur : G -> ");
	Serial.println(valG, BIN);
#endif
	byte valueConfigGauche = 0;
	if (valG) {
		valueConfigGauche = 1;
	}
	Wire.beginTransmission(ADD_CARTE_CODEUR_GAUCHE);
	Wire.write(CMD_SETUP);
	Wire.write(PARAM_INVERT);
	Wire.write(valueConfigGauche);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif

	// Codeur Droit
#ifdef DEBUG_MODE
	Serial.print(" * Configuration inversion codeur : D -> ");
	Serial.println(valD, BIN);
#endif
	byte valueConfigDroit = 0;
	if (valD) {
		valueConfigDroit = 1;
	}
	Wire.beginTransmission(ADD_CARTE_CODEUR_DROIT);
	Wire.write(CMD_SETUP);
	Wire.write(PARAM_INVERT);
	Wire.write(valueConfigDroit);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif
}
