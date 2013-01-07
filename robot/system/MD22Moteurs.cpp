/*
 * MD22Moteurs.cpp
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#include "MD22Moteurs.h"

#include <Arduino.h>
#include <Wire.h>

MD22Moteurs::MD22Moteurs() {
	alternate = false;
}

MD22Moteurs::~MD22Moteurs() {

}

void MD22Moteurs::moteurGauche(int val) {
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(LEFT_MOTOR);
	Wire.write(check(val));
	Wire.endTransmission();
}
void MD22Moteurs::moteurDroit(int val) {
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(RIGHT_MOTOR);
	Wire.write(check(val));
	Wire.endTransmission();
}

int MD22Moteurs::check(int val) {
	if (val < MIN_VAL) {
		val = MIN_VAL;
	}
	if (val > MAX_VAL) {
		val = MAX_VAL;
	}

	return val;
}

void MD22Moteurs::generateMouvement(int gauche, int droit) {
	alternate = !alternate;
	if (alternate) {
		moteurGauche(gauche);
		moteurDroit(droit);
	} else {
		moteurDroit(droit);
		moteurGauche(gauche);
	}
}
void MD22Moteurs::init() {
	// Set mode
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(MODE_REGISTER);
	Wire.write(MODE_VALUE);
	Wire.endTransmission();

	delayMicroseconds(100);

	// Set accelleration
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(ACCEL_REGISTER);
	Wire.write(ACCEL_VALUE);
	Wire.endTransmission();
}

void MD22Moteurs::printVersion() {
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(VERSION_REGISTER);
	Wire.endTransmission();

	Wire.requestFrom(ADD_BOARD, 1);
	while(Wire.available() < 1);
	int software = Wire.read();

	// TODO : Gérer le mode debug pour l'affichage de la version
	//Serial.print("MD22 V : ");
	//Serial.println(software);
}

