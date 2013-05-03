/*
 * Pid.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: mythril
 */

#include "Pid.h"

Pid::Pid() {
	kp = 0.1;
	kd = 0.5;
	ki = 0.25;

	errorSum = 0;
	lastError = 0;
}

void Pid::reset() {
	errorSum = 0;
	lastError = 0;
}

void Pid::setTunings(double kp, double ki, double kd) {
	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
}

double Pid::compute(double consigne, double mesure) {
	double error = consigne - mesure;
	double deltaError = error - lastError;
	lastError = error;
	errorSum += error;

	double result = kp * error + ki * errorSum + kd * deltaError;
	return result;
}
