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

Convertion::~Convertion() {
}

long int Convertion::mmToPulse(long int val) {
	return val * countPerMm;
}

long int Convertion::pulseToMm(long int val) {
	return val / countPerMm;
}

long int Convertion::degToPulse(long double val) {
	return val * countPerDegree;
}

long double Convertion::pulseToDeg(long int val) {
	return val / countPerDegree;
}

long double Convertion::pulseToRad(long int val) {
	return pulseToDeg(val * DEG_TO_RAD);
}

long int Convertion::radToPulse(long double val) {
	return degToPulse(val * RAD_TO_DEG);
}
