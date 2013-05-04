/*
 * ConsignePolaire.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef CONSIGNEPOLAIRE_H_
#define CONSIGNEPOLAIRE_H_

#include <Arduino.h>

#define FREIN_ACTIF 	0x01
#define FREIN_INACTIF 	0x00

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

	void setCmdGauche(int value);
	int getCmdGauche();

	void setCmdDroit(int value);
	int getCmdDroit();

	void enableFrein();
	void disableFrein();
	int getFrein();

private:
	long consigneDistance;
	word vitesseDistance;

	long consigneOrientation;
	word vitesseOrientation;

	int cmdDroit;
	int cmdGauche;

	int frein;
};

#endif /* CONSIGNEPOLAIRE_H_ */
