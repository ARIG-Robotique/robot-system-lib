/*
 * Pid.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: mythril
 */

#include "Pid.h"

#include <Arduino.h>

/*
 * Constructeur de la classe de gestion du PID
 */
Pid::Pid() {
	kp = 0.1;
	kd = 0.5;
	ki = 0.25;

	errorSum = 0;
	lastError = 0;
}

/*
 * Réinitialise les variables du PID
 */
void Pid::reset() {
	errorSum = 0;
	lastError = 0;
}

/*
 * Configuration des coëfficient du PID
 */
void Pid::setTunings(double kp, double ki, double kd) {
	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
}

/*
 * Calcul du PID en fonction de la consigne et de la mesure
 */
double Pid::compute(double consigne, double mesure) {
	double error = consigne - mesure;
	double deltaError = error - lastError;
	errorSum += error;
	double result = kp * error + ki * errorSum + kd * deltaError;

	lastError = error;
	return result;
}
