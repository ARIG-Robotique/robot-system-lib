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
 * M�thode pour placer un servo moteur
 */
void SD21::setPosition(byte servoNb, word position) {
	if (checkServo(servoNb)) {
		Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> P:");
		Serial.println(position, DEC);

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb) + 1);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		retCode = Wire.endTransmission();
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
	}
}

/*
 * M�thode pour d�finir la vitesse de rotation d'un servo moteur.
 */
void SD21::setSpeed(byte servoNb, byte speed) {
	if (checkServo(servoNb)) {
		Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> S:");
		Serial.println(speed, DEC);

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		retCode = Wire.endTransmission();
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
	}
}

/*
 * M�thode pour d�finir la vitesse et la position dans la m�me transmission I2C
 */
void SD21::setPositionAndSpeed(byte servoNb, byte speed, word position) {
	if (checkServo(servoNb)) {
		Serial.print("[Servo] ");
		Serial.print(servoNb);
		Serial.print(" -> S:");
		Serial.print(speed, DEC);
		Serial.print(" -> P:");
		Serial.println(position, DEC);

		Wire.beginTransmission(SD21_ADD_BOARD);
		Wire.write(getBaseRegister(servoNb));
		Wire.write(speed);
		Wire.write(position & 0xFF);
		Wire.write(position >> 8);
		retCode = Wire.endTransmission();
		if (i2cUtils.isError(retCode)) {
			i2cUtils.printReturnCode(retCode);
		}
	}
}

/*
 * Cette m�thode affiche la version de la carte sur la liaison serie en mode debug
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
		Serial.println(" - SD21 [KO]");
		i2cUtils.printReturnCode(retCode);
	}
}

/*
 * M�thode pour le contr�le du num�ro du servo
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
 * Par �xemple pour le servo 1 :
 *  0 : SPEED REGISTER
 *  1 : LOW BYTE POSITION REGISTER
 *  2 : HIGH BYTE POSITION REGISTER
 */
char SD21::getBaseRegister(byte servoNb) {
	return servoNb * 3 - 3;
}
