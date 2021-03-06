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

	void reset();

	double filter(double vitesse, double consigne, boolean frein);
	double filterLog(double vitesse, double consigne, double mesure, boolean frein); // /!\ EXPERIMENTAL

private:
	double sampleTime;
	double rampAcc;
	double rampDec;

	double stepVitesseAccel;
	double stepVitesseDecel;

	double vitesseCourante;
	double distanceDecel;
	double ecartPrecedent;

	void updateStepVitesse();
};

#endif /* QUAD_RAMP_H_ */
