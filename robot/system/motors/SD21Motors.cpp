/*
 * SD21Motors.cpp
 *
 *  Created on: 10 mai 2013
 *      Author: mythril
 */

#include "SD21Motors.h"

#include <Wire.h>

SD21Motors::SD21Motors() : AbstractMotors(), SD21() {
	minVal = 1100;
	maxVal = 1900;

	prevM1 = 1500;
	prevM2 = 1500;

	offsetValue = 1500;
}

SD21Motors::~SD21Motors() {
}

/*
 * Initialisation de la commande moteurs
 */
void SD21Motors::init() {
	stopAll();
}

/*
 * Envoi des commandes au moteur 1
 */
void SD21Motors::moteur1(int val) {
	int cmd = check(val + offsetValue);
	if (cmd == prevM1) {
		return;
	}
	prevM1 = cmd;

	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(getBaseRegister(MOTOR1_REGISTER) + 1);
	Wire.write(cmd & 0xFF);
	Wire.write(cmd >> 8);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif
}

/*
 * Envoi des commandes au moteur 2
 */
void SD21Motors::moteur2(int val) {
	int cmd = check(val + offsetValue);
	if (cmd == prevM2) {
		return;
	}
	prevM2 = cmd;

	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(getBaseRegister(MOTOR2_REGISTER) + 1);
	Wire.write(cmd & 0xFF);
	Wire.write(cmd >> 8);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif
}

#ifdef DEBUG_MODE
/*
 * Cette méthode affiche la version de la carte sur la liaison serie en mode debug
 */
void SD21Motors::printVersion() {
	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(SD21_VERSION_REGISTER);
	retCode = Wire.endTransmission();
	if (i2cUtils.isOk(retCode)) {
		Wire.requestFrom(SD21_ADD_BOARD, 1);
		while(Wire.available() < 1);
		int software = Wire.read();

		Serial.print(" - SD21 DC Motors [OK] (V : ");
		Serial.print(software);
		Serial.println(")");
	} else {
		Serial.print(" - SD21 DC Motors CMD [KO] ");
		i2cUtils.printReturnCode(retCode);
	}
}
#endif
