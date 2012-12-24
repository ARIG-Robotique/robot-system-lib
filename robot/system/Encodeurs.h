/*
 * Encodeurs.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ENCODEURS_H_
#define ENCODEURS_H_

class Encodeurs {
public:
	Encodeurs();
	virtual ~Encodeurs();

	void lectureValeurs();
	double getDistance();
	double getOrientation();

	void setValeursCodeurs(double gauche, double droit);
};

#endif /* ENCODEURS_H_ */
