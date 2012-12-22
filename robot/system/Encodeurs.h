/*
 * Encodeurs.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ENCODEURS_H_
#define ENCODEURS_H_

#include <Arduino.h>

class Encodeurs {
public:
	Encodeurs();
	virtual ~Encodeurs();

	void lectureValeurs();
	double getDistance();
	double getOrientation();

	void setValeursCodeurDroit();
	void setValeursCodeurGauche();
};

#endif /* ENCODEURS_H_ */
