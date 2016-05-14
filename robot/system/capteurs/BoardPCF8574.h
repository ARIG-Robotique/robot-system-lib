/*
 * BoardPCF8574.h
 *
 *  Created on: 7 avr. 2015
 *      Author: gdepuille
 */

#ifndef BOARDPCF8574_H_
#define BOARDPCF8574_H_

#include <Arduino.h>
#include <Wire.h>
#include "../../../common.h"

#define PCF8474_IO_COUNT 8

class BoardPCF8574 {
public:
	BoardPCF8574(const char * name, int address);

	void refresh();
	boolean readCapteurValue(byte capteurId);
	boolean readCapteurValue(byte capteurId, boolean refresh);
	void writeCapteurValue(byte capteurId, boolean value);
	void writeCapteurValues(byte values);

	void toggle(byte capteurId);

	void enableReverse(byte capteurId);
	void disableReverse(byte capteurId);

private :
	const char * name;
	int address;
	byte lastData;

	boolean capteurReverse[PCF8474_IO_COUNT];
};
#endif /* BOARDPCF8574_H_ */

