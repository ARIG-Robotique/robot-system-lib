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
	retCode = I2C_ACK;
}

/*
 * Méthode pour placer un servo moteur
 */
void SD21::setPosition(byte servoNb, word position) {
	if (checkServo(servoNb)) {
#ifdef DEBUG_MODE
		Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> P:");
		Serial.println(position, DEC);
#endif

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb) + 1);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
#endif
	}
}

/*
 * Méthode pour définir la vitesse de rotation d'un servo moteur.
 */
void SD21::setSpeed(byte servoNb, byte speed) {
	if (checkServo(servoNb)) {
#ifdef DEBUG_MODE
		/*Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> S:");
		Serial.println(speed, DEC);*/
#endif

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
#endif
	}
}

/*
 * Méthode pour définir la vitesse et la position dans la même transmission I2C
 */
void SD21::setPositionAndSpeed(byte servoNb, byte speed, word position) {
	if (checkServo(servoNb)) {
#ifdef DEBUG_MODE
		/*Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> S:");
		Serial.print(speed, DEC);
		Serial.print(" -> P:");
		Serial.println(position, DEC);*/
#endif

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
#endif
	}
}

#ifdef DEBUG_MODE
/*
 * Cette méthode affiche la version de la carte sur la liaison serie en mode debug
 */
void SD21::printVersion() {
	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(SD21_VERSION_REGISTER);
	retCode = Wire.endTransmission();
	if (i2cUtils.isOk(retCode)) {
		Wire.requestFrom(SD21_ADD_BOARD, 1);
		while(Wire.available() < 1);
		int software = Wire.read();

		Serial.print(" - SD21 [OK] (V : ");
		Serial.print(software);
		Serial.println(")");
	} else {
		Serial.print(" - SD21 [KO] ");
		i2cUtils.printReturnCode(retCode);
	}
}
#endif

/*
 * Méthode pour le contrôle du numéro du servo
 * Renvoi true si entre 1 et 21 inclus, false sinon
 */
boolean SD21::checkServo(byte servoNb) {
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
char SD21::getBaseRegister(byte servoNb) {
	return servoNb * 3 - 3;
}
