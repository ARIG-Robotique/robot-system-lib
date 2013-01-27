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

	void lectureValeurs();
	double getDistance();
	double getOrientation();

	void setValeursCodeurs(double gauche, double droit);
	void reset();

protected:
	double distance, orientation;

private:
	#define CMD_LECTURE 'l'
	#define CMD_RESET	'r'

	#define ADD_CARTE_CODEUR_DROIT 0xB0
	#define ADD_CARTE_CODEUR_GAUCHE 0xB2

	bool alternate;

	double lectureGauche();
	double lectureDroit();
	double lectureData(int address);
};

#endif /* ENCODEURS_H_ */
