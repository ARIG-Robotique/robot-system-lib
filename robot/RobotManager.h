/*
 * RobotManager.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

#include "../common.h"

// Value Object
#include "vo/RobotConsigne.h"
#include "vo/ConsignePolaire.h"

// Business elements
#include "system/Encodeurs.h"
#include "system/Odometrie.h"
#include "system/Asservissement.h"
#include "system/motors/MD22.h"

class RobotManager {
public:
	RobotManager();

	void init();
	void resetEncodeurs();
	void process();
	void stop();

	// Consigne a atteindre
	void setConsigneTable(RobotConsigne rc);

	// Configuration de l'asservissement
	void setSampleTime(int sampleTime);
	void setPIDDistance(double kp, double ki, double kd);
	void setPIDOrientation(double kp, double ki, double kd);
	void setRampAcc(double rampDistance, double rampOrientation);
	void setRampDec(double rampDistance, double rampOrientation);

	// Getter pour les enchainement de valeurs
	boolean getTrajetAtteint();
	boolean getTrajetEnApproche();

	// Pour la modification de la vitesse a chaud
	void setVitesse(word vDistance, word vOrientation);

private:
	#define FENETRE_ARRET_DISTANCE			4  		// +- 4 pulse pour l'arret -> 1mm
	#define FENETRE_ARRET_ORIENTATION		11 		// +- 11,36 pulse pour l'arret -> 1°

	#define FENETRE_EN_APPROCHE_DISTANCE	80 		// +- 80 pulse pour la reception de la nouvelle position -> 2 cm
	#define FENETRE_EN_APPROCHE_ORIENTATION 57 		// +- 56,8 pulse pour la reception de la nouvelle position -> 5°

	Odometrie odom;
	Encodeurs enc;
	ConsignePolaire consignePolaire;
	Asservissement asserv;
	MD22 moteurs;

	RobotConsigne consigneTable;

	unsigned long timePrec;
	unsigned long time;

	boolean trajetAtteint;
	boolean trajetEnApproche;

	void calculConsigne();
};

#endif /* ROBOTMANAGER_H_ */
