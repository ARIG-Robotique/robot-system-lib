/*
 * BoardPCF8574.cpp
 *
 *  Created on: 7 avr. 2015
 *      Author: gdepuille
 */


#include "BoardPCF8574.h"

BoardPCF8574::BoardPCF8574(const char * name, int address) {
	this->name = name;
	this->address = address;

	// Initialisation
	lastData = 0xFF;

	for(int i = 0 ; i < PCF8474_IO_COUNT ; i++) {
		capteurReverse[i] = true;
	}
}


void BoardPCF8574::refresh() {
	Wire.beginTransmission(address);
	Wire.requestFrom(address, 1);
	lastData = Wire.read();
	Wire.endTransmission();
}

boolean BoardPCF8574::readCapteurValue(byte capteurId) {
	return this->readCapteurValue(capteurId, true);
}

boolean BoardPCF8574::readCapteurValue(byte capteurId, boolean refresh) {
	if (refresh) {
		this->refresh();
	}

	boolean result = (lastData & (1 << capteurId)) > 0;
	return (capteurReverse[capteurId]) ? !result : result;
}

void BoardPCF8574::writeCapteurValue(byte capteurId, boolean value) {
	refresh();
	if (value) {
		lastData &= ~(1 << capteurId);
	} else {
		lastData |= (1 << capteurId);
	}
	writeCapteurValues(lastData);
}

void BoardPCF8574::writeCapteurValues(byte values) {
	Wire.beginTransmission(address);
	lastData = values;
	Wire.write(lastData);
	Wire.endTransmission();
}

void BoardPCF8574::toggle(byte capteurId) {
	refresh();
	lastData ^= (1 << capteurId);
	writeCapteurValues(lastData);
}

void BoardPCF8574::enableReverse(byte capteurId) {
	capteurReverse[capteurId] = true;
}

void BoardPCF8574::disableReverse(byte capteurId) {
	capteurReverse[capteurId] = false;
}
