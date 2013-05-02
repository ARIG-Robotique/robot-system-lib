/*
 * ConsignePolaire.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef CONSIGNEPOLAIRE_H_
#define CONSIGNEPOLAIRE_H_

#include <Arduino.h>

class ConsignePolaire {
public:
	ConsignePolaire();

	void setConsigneDistance(double value);
	double getConsigneDistance();

	void setVitesseDistance(double value);
	double getVitesseDistance();

	void setConsigneOrientation(double value);
	double getConsigneOrientation();

	void setVitesseOrientation(double value);
	double getVitesseOrientation();

	void setCmdGauche(int value);
	int getCmdGauche();

	void setCmdDroit(int value);
	int getCmdDroit();

	void enableFrein();
	void disableFrein();
	boolean isFreinEnable();

private:
	double consigneDistance;
	double vitesseDistance;

	double consigneOrientation;
	double vitesseOrientation;

	int cmdDroit;
	int cmdGauche;

	boolean frein;
};

#endif /* CONSIGNEPOLAIRE_H_ */
