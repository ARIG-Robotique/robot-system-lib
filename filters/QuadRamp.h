/*
 * QuadRamp.h
 *
 *  Created on: 7 janv. 2013
 *      Author: mythril
 */

#ifndef QUAD_RAMP_H_
#define QUAD_RAMP_H_

#include <Arduino.h>
#include "../common.h"

class QuadRamp {
public:
	QuadRamp();
	QuadRamp(double sampleTime, double rampAcc, double rampDec);

	void setSampleTimeMs(double value);
	void setRampAcc(double value);
	void setRampDec(double value);

	double filter(double vitesse, double consigne, byte frein);
	double filterLog(double vitesse, double consigne, double mesure, byte frein); // /!\ EXPERIMENTAL

private:
	double sampleTime;
	double rampAcc;
	double rampDec;

	double vitesseCourante;
	double distanceDecel;
	double ecartPrecedent;
};

#endif /* QUAD_RAMP_H_ */
