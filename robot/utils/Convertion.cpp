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

long Convertion::mmToPulse(long val) {
	return val * countPerMm;
}

long Convertion::pulseToMm(long val) {
	return val / countPerMm;
}

long Convertion::degToPulse(long val) {
	return val * countPerDegree;
}

long Convertion::pulseToDeg(long val) {
	return val / countPerDegree;
}

long Convertion::pulseToRad(long val) {
	return pulseToDeg(val * DEG_TO_RAD);
}

long Convertion::radToPulse(long val) {
	return degToPulse(val * RAD_TO_DEG);
}
