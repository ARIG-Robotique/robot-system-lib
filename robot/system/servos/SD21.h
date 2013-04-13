/*
 * SD21.h
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 */

#ifndef SD21_H_
#define SD21_H_

#include <Arduino.h>

class SD21 {
public:
	SD21();

	void setPosition(char servoNb, int position);
	void setSpeed(char servoNb, char speed);
	void setPositionAndSpeed(int servoNb, char speed, int position);


private:
	#define ADD_BOARD				0x61

	#define VERSION_REGISTER		0x40

	void init();
	boolean checkServo(char servoNb);
	char getBaseRegister(char servoNb);
	void printVersion();
};

#endif /* SD21_H_ */
