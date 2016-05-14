/*
 * Convertion.h
 *
 *  Created on: 24 déc. 2012
 *      Author: mythril
 */

#ifndef CONVERTION_H_
#define CONVERTION_H_

#include <Arduino.h>

// /!\ Doit être instancié dans le fichier main de l'application
// Convertion Conv = Convertion(4.044, 11.36);
//
// La configuration des coëficients est à effctuer pour chaque robot avec le fichier Excel

class Convertion {
public:
	Convertion(double, double);

	double mmToPulse(double);
	double pulseToMm(double);
	double degToPulse(double);
	double pulseToDeg(double);
	double pulseToRad(double);
	double radToPulse(double);

	double getPiPulse();
	double get2PiPulse();

private:
	double countPerMm;
	double countPerDegree;

	double piPulse;
	double pi2Pulse;
};

extern Convertion Conv;

#endif /* CONVERTION_H_ */
