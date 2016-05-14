/*
 * SD21Motors.h
 *
 *  Created on: 10 mai 2013
 *      Author: mythril
 */

#ifndef SD21MOTORS_H_
#define SD21MOTORS_H_

#include <Arduino.h>
#include <Wire.h>
#include "AbstractPropulsionMotors.h"
#include "../servos/SD21.h"
#include "../../../common.h"
#include "../../../utils/I2CUtils.h"

class SD21Motors: public AbstractPropulsionMotors, public SD21 {
public:
	SD21Motors(byte address);
	virtual ~SD21Motors();

	// Implémentation méthode virtuel //
	virtual void init();
	virtual void moteur1(int cmd);
	virtual void moteur2(int cmd);

#ifdef LIB_DEBUG_MODE
	virtual void printVersion();
#endif

private:
	#define MOTOR1_REGISTER			13
	#define MOTOR2_REGISTER			14

	int offsetValue;
};

#endif /* SD21MOTORS_H_ */
