/*
 * Asservissement.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef ASSERVISSEMENT_H_
#define ASSERVISSEMENT_H_

#include "../../filters/Pid.h"
#include "../../filters/QuadRamp.h"
#include "../vo/ConsignePolaire.h"
#include "encoders/ARIGEncodeurs.h"

class Asservissement {
public:
	Asservissement();
	Asservissement(byte sampleTime);

	void setSampleTimeMs(byte sampleTime);
	byte getSampleTimeMs();

	void setPIDDistance(double kp, double ki, double kd);
	void setPIDOrientation(double kp, double ki, double kd);

	void setRampAcc(double rampDistance, double rampOrientation);
	void setRampDec(double rampDistance, double rampOrientation);

	void process(ARIGEncodeurs & encodeurs, ConsignePolaire & consignePolaire);

	void reset();
	void reset(boolean resetFilters);

	double getFenetreApprocheDistance();
	double getFenetreApprocheOrientation();

private:
	Pid pidOrientation;
	Pid pidDistance;
	QuadRamp filterDistance;
	QuadRamp filterOrientation;

	double setPointDistance;
	double setPointOrientation;

	double inputDistance;
	double inputOrientation;

	double outputDistance;
	double outputOrientation;

	double minFenetreDistance;
	double minFenetreOrientation;

	byte sampleTime;

	void setup();
};

#endif /* ASSERVISSEMENT_H_ */
