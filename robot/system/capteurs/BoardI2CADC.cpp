/*
 * BoardI2CADC.cpp
 *
 *  Created on: 12 avr. 2015
 *      Author: gdepuille
 */

#include "BoardI2CADC.h"

BoardI2CADC::BoardI2CADC(int address) {
	this->address = address;
	this->sdMode = SINGLE_ENDED_INPUTS;
	this->powerDownMode = POWER_DOWN_BETWEEN_AD;
}

void BoardI2CADC::inputMode(byte value) {
	this->sdMode = value;
}

void BoardI2CADC::powerDown(byte value) {
	this->powerDownMode = value;
}

int BoardI2CADC::readCapteurValue(byte capteurId) {

	// Construction du registre de lecture
	byte MSB = 0, LSB = 0;
	byte reg = (sdMode << 7) + (CH_ADD[capteurId] << 4) + (powerDownMode << 2);

	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.endTransmission();;
	delay(1);

	// Read A/D value
	Wire.requestFrom(address, 2);
	while(Wire.available()) { // Check for data from slave
		MSB = Wire.read(); // Receive A/D high byte
		LSB = Wire.read(); // Receive A/D low byte
	}
	int result = (MSB << 8) + LSB;

#ifdef LIB_DEBUG_MODE
	Serial.print("Lecture analogique capt. ");Serial.print(capteurId);
	Serial.print(" (Ox");Serial.print(reg , HEX);Serial.print(") = ");
	Serial.println(result, DEC);
#endif

	return result;
}
