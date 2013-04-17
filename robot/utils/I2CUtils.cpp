/*
 * I2CUtils.cpp
 *
 *  Created on: 14 avr. 2013
 *      Author: mythril
 */

#include "I2CUtils.h"

I2CUtils::I2CUtils() {
}

#ifdef DEBUG_MODE
/*
 * Fonction permettant d'afficher le résultat d'une commande I2C
 */
void I2CUtils::printReturnCode(byte code) {
	switch (code) {
	case I2C_ACK : // OK
		Serial.println("[I2C - OK] Success");
		break;
	case I2C_DATA_TOO_LONG :
		Serial.println("[I2C - ERROR] Data Too long");
		break;
	case I2C_NACK_BAD_ADDRESS :
		Serial.println("[I2C - ERROR] Bad address");
		break;
	case I2C_NACK_BAD_DATA :
		Serial.println("[I2C - ERROR] Bad data");
		break;
	case I2C_OTHER_ERROR :
		Serial.println("[I2C - ERROR] Unknown error");
		break;
	}
}
#endif

/*
 * Contrôle si le code de retour est une erreur
 */
boolean I2CUtils::isError(byte code) {
	return code != I2C_ACK;
}

/*
 * Contrôle si le code de retour est OK
 */
boolean I2CUtils::isOk(byte code) {
	return code == I2C_ACK;
}

I2CUtils i2cUtils = I2CUtils();
