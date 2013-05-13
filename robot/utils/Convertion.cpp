/*
 * Convertion.cpp
 *
 *  Created on: 24 déc. 2012
 *      Author: mythril
 */

#include "Convertion.h"

#include <Arduino.h>

Convertion::Convertion(double countPerMm, double countPerDegree) {
	this->countPerMm = countPerMm;
	this->countPerDegree = countPerDegree;
}

double Convertion::mmToPulse(double val) {
	return val * countPerMm;
}

double Convertion::pulseToMm(double val) {
	return val / countPerMm;
}

double Convertion::degToPulse(double val) {
	return val * countPerDegree;
}

double Convertion::pulseToDeg(double val) {
	return val / countPerDegree;
}

double Convertion::pulseToRad(double val) {
	return pulseToDeg(val * DEG_TO_RAD);
}

double Convertion::radToPulse(double val) {
	return degToPulse(val * RAD_TO_DEG);
}
