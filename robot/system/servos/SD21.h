/*
 * SD21.h
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#ifndef SD21_H_
#define SD21_H_

#include <Arduino.h>
#include "../../utils/I2CUtils.h"

class SD21 {
public:
	SD21();

	void printVersion();
	void setPosition(byte servoNb, word position);
	void setSpeed(byte servoNb, byte speed);
	void setPositionAndSpeed(byte servoNb, byte speed, word position);


private:
	#define SD21_ADD_BOARD				0x61

	#define SD21_VERSION_REGISTER		0x40

	byte retCode;
	boolean checkServo(byte servoNb);
	char getBaseRegister(byte servoNb);
};

#endif /* SD21_H_ */
