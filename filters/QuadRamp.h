/*
 * QuadRamp.h
 *
 *  Created on: 7 janv. 2013
 *      Author: mythril
 */

#ifndef QUAD_RAMP_H_
#define QUAD_RAMP_H_

class QuadRamp {
public:
	QuadRamp();
	QuadRamp(int sampleTime, double rampAcc, double rampDec);

	void setSampleTimeMs(int value);
	void setRampAcc(double value);
	void setRampDec(double value);

	double filter(double vitesse, double consigne, double mesure, bool frein);

private:
	int sampleTime;
	double rampAcc;
	double rampDec;

	double vitesseCourante;
	double distanceDecel;
	double ecartPrecedent;
};

#endif /* QUAD_RAMP_H_ */
