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
 * Méthode pour placer un servo moteur
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
 * Méthode pour définir la vitesse de rotation d'un servo moteur.
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
 * Méthode pour définir la vitesse et la position dans la même transmission I2C
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
 * Cette méthode affiche la version de la carte sur la liaison serie en mode debug
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
 * Méthode pour le contrôle du numéro du servo
 * Renvoi true si entre 1 et 21 inclus, false sinon
 */
boolean SD21::checkServo(char servoNb) {
	if (servoNb >= 1 && servoNb <= 21) {
		return true;
	}

	return false;
}

/*
 * Renvoi le registre de base pour un servo.
 * Par éxemple pour le servo 1 :
 *  0 : SPEED REGISTER
 *  1 : LOW BYTE POSITION REGISTER
 *  2 : HIGH BYTE POSITION REGISTER
 */
char SD21::getBaseRegister(char servoNb) {
	return servoNb * 3 - 3;
}
