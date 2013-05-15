/*
 * Pid.cpp
 *
 *  Created on: 3 mai 2013
 *      Author: mythril
 */

#include "Pid.h"

#ifdef DEBUG_MODE
#include <Arduino.h>
#endif

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

	//FIXME : A ameliorer
	if(errorSum+error>34000000000.0) errorSum= 34000000000.0;
	else if(errorSum+error<-34000000000.0) errorSum= -34000000000.0;
	else errorSum += error;

	lastError = error;
	double result = kp * error + ki * errorSum + kd * deltaError;

#ifdef DEBUG_MODE
	Serial.print(";PIDCons ");Serial.print(consigne);
	Serial.print(";PIDMes ");Serial.print(mesure);
	Serial.print(";PIDsumErr ");Serial.print(errorSum);
	Serial.print(";PIDresult ");Serial.print(result);
#endif

	return result;
}
