/*
 * Convertion.h
 *
 *  Created on: 24 déc. 2012
 *      Author: mythril
 */

#ifndef CONVERTION_H_
#define CONVERTION_H_

// A configurer pour chaque robot;
//#define COUNT_PER_MM				4.044	 			// Nombre d'impulsion codeur pour 1mm
//#define COUNT_PER_DEG				11.36 				// 5.68 * 2 Nombre de count pour réalisé 1°

// /!\ Doit être instancié dans le fichier main de l'application
// Convertion Conv = Convertion(4.044, 11.36);

class Convertion {
public:
	Convertion(double, double);

	double mmToPulse(double);
	double pulseToMm(double);
	double degToPulse(double);
	double pulseToDeg(double);
	double pulseToRad(double);
	double radToPulse(double);

private:
	double countPerMm;
	double countPerDegree;
};

extern Convertion Conv;

#endif /* CONVERTION_H_ */
