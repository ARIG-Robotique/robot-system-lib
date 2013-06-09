/*
 * SD21Motors.cpp
 *
 *  Created on: 10 mai 2013
 *      Author: mythril
 */

#include "SD21Motors.h"

#include <Wire.h>

SD21Motors::SD21Motors() {
 minVal = 1100;
 stopVal = 1500;
 maxVal = 1900;

 prevGauche = 1500;
 prevDroit = 1500;

 alternate = false;
}

void SD21Motors::generateMouvement(int gauche, int droit) {
	alternate = !alternate;
	if (alternate) {
		moteurGauche(gauche);
		moteurDroit(droit);
	} else {
		moteurDroit(droit);
		moteurGauche(gauche);
	}
}

void SD21Motors::moteurGauche(int val) {
	int cmd = check(val + stopVal);
	if (cmd == prevGauche) {
		return;
	}
	prevGauche = cmd;

	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(getBaseRegister(LEFT_MOTOR_REGISTER) + 1);
	Wire.write(cmd & 0xFF);
	Wire.write(cmd >> 8);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif
}

void SD21Motors::moteurDroit(int val) {
	int cmd = check(val + stopVal);
	if (cmd == prevDroit) {
		return;
	}
	prevDroit = cmd;

	Wire.beginTransmission(SD21_ADD_BOARD);
	Wire.write(getBaseRegister(RIGHT_MOTOR_REGISTER) + 1);
	Wire.write(cmd & 0xFF);
	Wire.write(cmd >> 8);
	retCode = Wire.endTransmission();
#ifdef DEBUG_MODE
	if (i2cUtils.isError(retCode)) {
		i2cUtils.printReturnCode(retCode);
	}
#endif
}

void SD21Motors::stopAll() {
	stopDroit();
	stopGauche();
}

void SD21Motors::stopGauche() {
	moteurGauche(0);
}

void SD21Motors::stopDroit() {
	moteurDroit(0);
}

int SD21Motors::check(int val) {
	if (val < minVal) {
		val = minVal;
	}
	if (val > maxVal) {
		val = maxVal;
	}

	return val;
}
