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

	void setConsigneDistance(long value);
	long getConsigneDistance();

	void setVitesseDistance(word value);
	word getVitesseDistance();

	void setConsigneOrientation(long value);
	long getConsigneOrientation();

	void setVitesseOrientation(word value);
	word getVitesseOrientation();

	void setCmdGauche(char value);
	char getCmdGauche();

	void setCmdDroit(char value);
	char getCmdDroit();

	void enableFrein();
	void disableFrein();
	boolean isFreinEnable();

private:
	long consigneDistance;
	word vitesseDistance;

	long consigneOrientation;
	word vitesseOrientation;

	char cmdDroit;
	char cmdGauche;

	boolean frein;
};

#endif /* CONSIGNEPOLAIRE_H_ */
