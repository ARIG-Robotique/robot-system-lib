/*
 * AbstractEncodeurs.h
 *
 *  Created on: 25 juin 2013
 *      Author: mythril
 */

#ifndef ABSTRACTENCODEURS_H_
#define ABSTRACTENCODEURS_H_

class AbstractEncodeurs {
public:
	AbstractEncodeurs();
	virtual ~AbstractEncodeurs();

	void lectureValeurs();
	double getDistance();
	double getOrientation();
	void setCoefs(double coefGauche, double coefDroit);

	// ------------------ //
	// Méthode abstraites //
	// ------------------ //
	virtual void reset() = 0;

protected:

	// ------------------ //
	// Méthode abstraites //
	// ------------------ //
	virtual double lectureGauche() = 0;
	virtual double lectureDroit() = 0;

private:
	double distance, orientation;
	double coefGauche, coefDroit;

	void setValeursCodeurs(double gauche, double droit);
};

#endif /* ABSTRACTENCODEURS_H_ */
