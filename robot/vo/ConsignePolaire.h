/*
 * ConsignePolaire.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef CONSIGNEPOLAIRE_H_
#define CONSIGNEPOLAIRE_H_

class ConsignePolaire {
public:
	ConsignePolaire();
	virtual ~ConsignePolaire();

	void setConsigneDistance(double value);
	double getConsigneDistance();

	void setVitesseDistance(double value);
	double getVitesseDistance();

	void setConsigneOrientation(double value);
	double getConsigneOrientation();

	void setVitesseOrientation(double value);
	double getVitesseOrientation();

	void enableFrein();
	void disableFrein();
	bool isFreinEnable();

private:
	double consigneDistance;
	double vitesseDistance;
	double consigneOrientation;
	double vitesseOrientation;
	bool frein;
};

#endif /* CONSIGNEPOLAIRE_H_ */
