/*
 * PWMMotor.cpp
 *
 *  Created on: 19 avr. 2015
 *      Author: gdepuille
 */

#include "PWMMotor.h"

PWMMotor::PWMMotor(byte dirPin, byte pwmPin) {
	this->dirPin = dirPin;
	this->pwmPin = pwmPin;
}

PWMMotor::PWMMotor(byte dirPin, byte pwmPin, byte currentPin) {
	this->dirPin = dirPin;
	this->pwmPin = pwmPin;
	this->currentPin = currentPin;
}

void PWMMotor::stop() {
	cmd(0);
}

void PWMMotor::cmd(int val) {
	int cmd = check(val);
	if (cmd == prev) {
		return;
	}
	prev = cmd;

	digitalWrite(dirPin, (cmd >= 0) ? HIGH : LOW);
	analogWrite(pwmPin, abs(cmd));
}

/*
 * Méthode permettant de lire la consommation du moteur.
 * Renvoi -1 si non configuré
 */
int PWMMotor::current() {
	if (this->currentPin == PWM_UNDEF_PIN) {
		return -1;
	}

	return analogRead(this->currentPin);
}

/*
 * Méthode de contrôle du bornage des commandes moteurs
 */
int PWMMotor::check(int val) {
	if (val < minVal) {
		val = minVal;
	}
	if (val > maxVal) {
		val = maxVal;
	}

	return val;
}

void PWMMotor::setMin(int minVal) { this->minVal = minVal; }
void PWMMotor::setMax(int maxVal) { this->maxVal = maxVal; }
