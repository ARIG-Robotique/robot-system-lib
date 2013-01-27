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

	void setConsigneDistance(double value);
	double getConsigneDistance();

	void setSetPointDistance(double value);
	double getSetPointDistance();

	void setVitesseDistance(double value);
	double getVitesseDistance();

	void setConsigneOrientation(double value);
	double getConsigneOrientation();

	void setSetPointOrientation(double value);
	double getSetPointOrientation();

	void setVitesseOrientation(double value);
	double getVitesseOrientation();

	void setCmdGauche(int value);
	int getCmdGauche();

	void setCmdDroit(int value);
	int getCmdDroit();

	void enableFrein();
	void disableFrein();
	bool isFreinEnable();

private:
	double consigneDistance;
	double setPointDistance;
	double vitesseDistance;

	double consigneOrientation;
	double setPointOrientation;
	double vitesseOrientation;

	int cmdDroit;
	int cmdGauche;

	bool frein;
};

#endif /* CONSIGNEPOLAIRE_H_ */
