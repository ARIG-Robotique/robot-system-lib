/*
 * I2CUtils.h
 *
 *  Created on: 14 avr. 2013
 *      Author: mythril
 */

#ifndef I2CUTILS_H_
#define I2CUTILS_H_

#include <Arduino.h>

#include "../../common.h"

#define I2C_ACK					0
#define I2C_DATA_TOO_LONG		1
#define I2C_NACK_BAD_ADDRESS	2
#define I2C_NACK_BAD_DATA		3
#define I2C_OTHER_ERROR			4

class I2CUtils {
public:
	I2CUtils();

	boolean isError(byte code);
	boolean isOk(byte code);

#ifdef DEBUG_MODE
	void printReturnCode(byte code);
#endif
};

extern I2CUtils i2cUtils;

#endif /* I2CUTILS_H_ */
