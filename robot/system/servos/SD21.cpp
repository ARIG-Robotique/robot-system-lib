/*
 * SD21.cpp
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#include "SD21.h"

#include <Arduino.h>
#include <Wire.h>

SD21::SD21() {
	init();
}

/*
 * Initialisation de la carte MD22.
 * La configuration du mode
 */
void SD21::init() {
	printVersion();
}

/*
 * M�thode pour placer un servo moteur
 */
void SD21::setPosition(char servoNb, int position) {
	if (checkServo(servoNb)) {
		Wire.beginTransmission(ADD_BOARD);
		Wire.write(getBaseRegister(servoNb) + 1);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		Wire.endTransmission();
	}
}

/*
 * M�thode pour d�finir la vitesse de rotation d'un servo moteur.
 */
void SD21::setSpeed(char servoNb, char speed) {
	if (checkServo(servoNb)) {
		Wire.beginTransmission(ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		Wire.endTransmission();
	}
}

/*
 * M�thode pour d�finir la vitesse et la position dans la m�me transmission I2C
 */
void SD21::setPositionAndSpeed(int servoNb, char speed, int position) {
	if (checkServo(servoNb)) {
		Wire.beginTransmission(ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		Wire.endTransmission();
	}
}

/*
 * Cette m�thode affiche la version de la carte sur la liaison serie en mode debug
 */
void SD21::printVersion() {
#ifdef DEBUG_MODE
	Wire.beginTransmission(ADD_BOARD);
	Wire.write(VERSION_REGISTER);
	Wire.endTransmission();

	Wire.requestFrom(ADD_BOARD, 1);
	while(Wire.available() < 1);
	int software = Wire.read();

	Serial.print("SD21 software V : ");
	Serial.println(software);
#endif
}

/*
 * M�thode pour le contr�le du num�ro du servo
 * Renvoi true si entre 1 et 21 inclus, false sinon
 */
boolean checkServo(char servoNb) {
	if (servoNb >= 1 && servoNb <= 21) {
		return true;
	}

	return false;
}

/*
 * Renvoi le registre de base pour un servo.
 * Par �xemple pour le servo 1 :
 *  0 : SPEED REGISTER
 *  1 : LOW BYTE POSITION REGISTER
 *  2 : HIGH BYTE POSITION REGISTER
 */
char getBaseRegister(char servoNb) {
	return servoNb * 3 - 3;
}
