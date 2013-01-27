/*
 * Asservissement.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

#include "../../filters/PID_v1.h"
#include "../../filters/QuadRamp.h"
#include "../vo/ConsignePolaire.h"
#include "Encodeurs.h"

class Asservissement {
public:
	Asservissement();
	Asservissement(int sampleTime);

	void setSampleTime(int sampleTime);
	void setPIDDistance(double kp, double ki, double kd);
	void setPIDOrientation(double kp, double ki, double kd);
	void setRampAcc(double rampDistance, double rampOrientation);
	void setRampDec(double rampDistance, double rampOrientation);

	void process(Encodeurs * encodeurs, ConsignePolaire * consignePolaire);

private:
	PID pidOrientation;
	PID pidDistance;
	QuadRamp filterDistance;
	QuadRamp filterOrientation;

	double consigneDistance;
	double consigneOrientation;

	double outputDistance;
	double outputOrientation;

	double inputDistance;
	double inputOrientation;

	int sampleTime;

	void setup();
};

#endif /* ASSERVISSEMENT_H_ */
