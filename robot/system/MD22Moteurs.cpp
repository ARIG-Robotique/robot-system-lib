/*
 * MD22Moteurs.cpp
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#include "MD22Moteurs.h"

#include <Arduino.h>
#include <Wire.h>

#define ADD_BOARD			0xB4

#define MODE_REGISTER		0x00
#define MODE_VALUE			1 // -128 (Reverse) - 0 (Stop) - 127 (Forward)

#define LEFT_MOTOR			1
#define RIGHT_MOTOR			2

#define VERSION_REGISTER	7

#define ACCEL_REGISTER		3
#define ACCEL_VALUE			20

MD22Moteurs::MD22Moteurs() {
	alternate = false;
}

MD22Moteurs::~MD22Moteurs() {

}

void MD22Moteurs::moteurGauche(int val) {
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(LEFT_MOTOR);
	Wire.write(val);
	Wire.endTransmission();
}
void MD22Moteurs::moteurDroit(int val) {
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(RIGHT_MOTOR);
	Wire.write(val);
	Wire.endTransmission();
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
	Wire.write(VERSION_REGISTER); // Calls software register
	Wire.endTransmission();

	Wire.requestFrom(ADD_BOARD, 1); // Requests one byte
	while(Wire.available() < 1); // Wait for it to arrive
	int software = Wire.read(); // Get byte
	Serial.print("MD22 V : ");
	Serial.println(software);
}

