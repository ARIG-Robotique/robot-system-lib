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
#include "../../../common.h"
#include "../../../utils/I2CUtils.h"
#include "../servos/SD21.h"

class SD21Motors: public SD21 {
public:
	SD21Motors();

	void generateMouvement(int gauche, int droit);
	void moteurGauche(int);
	void moteurDroit(int);
	void stopAll();
	void stopGauche();
	void stopDroit();

private:

	bool alternate;

private:

	#define MOTOR1_REGISTER			13
	#define MOTOR2_REGISTER			14

	#define RIGHT_MOTOR_REGISTER	MOTOR1_REGISTER
	#define LEFT_MOTOR_REGISTER		MOTOR2_REGISTER

	int minVal;
	int maxVal;
	int stopVal;

	int prevGauche;
	int prevDroit;

	int check(int);
};

#endif /* SD21MOTORS_H_ */
