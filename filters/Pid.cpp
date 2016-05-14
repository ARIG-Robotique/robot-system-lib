/*
 * Pid.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: mythril
 */

#include "Pid.h"

#ifdef LIB_DEBUG_MODE
#include <Arduino.h>
#endif

/*
 * Constructeur de la classe de gestion du PID
 */
Pid::Pid() {
	kp = 0.8;
	kd = 0.2;
	ki = 0.1;

	reset();
}

/*
 * Réinitialise les cumuls d'erreur du PID
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
	lastError = error;
	double result = kp * error + ki * errorSum + kd * deltaError;

#ifdef LIB_DEBUG_MODE
	Serial.print(";");Serial.print(consigne);
	Serial.print(";");Serial.print(mesure);
	Serial.print(";");Serial.print(errorSum);
	Serial.print(";");Serial.print(result);
#endif

	return result;
}

double Pid::getError() { return errorSum; }
