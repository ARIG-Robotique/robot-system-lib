/*
 * SD21.h
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#ifndef SD21_H_
#define SD21_H_

#include <Arduino.h>
#include "../../../common.h"
#include "../../utils/I2CUtils.h"

class SD21 {
public:
	SD21();

	void setPosition(byte servoNb, word position);
	void setSpeed(byte servoNb, byte speed);
	void setPositionAndSpeed(byte servoNb, byte speed, word position);

#ifdef DEBUG_MODE
	void printVersion();
#endif

protected:
	#define SD21_ADD_BOARD				0x61

	char getBaseRegister(byte servoNb);
	byte retCode;

private:

	#define SD21_VERSION_REGISTER		0x40

	boolean checkServo(byte servoNb);
};

#endif /* SD21_H_ */
