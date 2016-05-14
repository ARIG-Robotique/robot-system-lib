/*
 * PWMMotor.h
 *
 *  Created on: 19 avr. 2015
 *      Author: gdepuille
 */

#ifndef PWMMOTOR_H_
#define PWMMOTOR_H_

#include <Arduino.h>
#include "../../../common.h"

class PWMMotor {
public:


	PWMMotor(byte dirPin, byte pwmPin);
	PWMMotor(byte dirPin, byte pwmPin, byte currentPin);

	void stop();
	void cmd(int cmd);
	int current();
	void setMin(int minVal);
	void setMax(int maxVal);

private:
	#define PWM_UNDEF_PIN	-1
	#define PWM_MAX 		255

	byte dirPin;
	byte pwmPin;
	byte currentPin = PWM_UNDEF_PIN;

	int prev = 0;
	int minVal = -PWM_MAX;
	int maxVal = PWM_MAX;

	int check(int val);
};

#endif /* PWMMOTOR_H_ */
