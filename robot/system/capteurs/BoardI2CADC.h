/*
 * BoardI2CADC.h
 *
 *  Created on: 12 avr. 2015
 *      Author: gdepuille
 */

#ifndef BOARDI2CADC_H_
#define BOARDI2CADC_H_

#include <Arduino.h>
#include <Wire.h>
#include "../../../common.h"

#define I2C_ADC_IO_COUNT 		8

#define DIFFERENTIAL_INPUTS 	0
#define SINGLE_ENDED_INPUTS 	1

#define POWER_DOWN_BETWEEN_AD 	0
#define INTERNAL_REF_OFF_AD_ON 	1
#define INTERNAL_REF_ON_AD_OFF	2
#define INTERNAL_REF_ON_AD_ON	3

class BoardI2CADC {
public:
	BoardI2CADC(int address);

	void inputMode(byte value);
	void powerDown(byte value);

	int readCapteurValue(byte capteurId);
private:
	// Adresse des canaux ADC
	const byte CH_ADD[I2C_ADC_IO_COUNT] = {0, 4, 1, 5, 2, 6, 3, 7};
	int address;
	byte sdMode;
	byte powerDownMode;
};

#endif /* BOARDI2CADC_H_ */
