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
#include "system/motors/SD21Motors.h"

class RobotManager {
public:
	RobotManager();

	void init();
	void resetEncodeurs();
	void process();
	void stop();

	// Consigne a atteindre
	void setConsigneTable(RobotConsigne rc);

	void setPosition(double x, double y, double angle);
	RobotPosition getPosition();

	// Configuration de l'asservissement
	void setSampleTime(int sampleTime);
	void setPIDDistance(double kp, double ki, double kd);
	void setPIDOrientation(double kp, double ki, double kd);
	void setRampAcc(double rampDistance, double rampOrientation);
	void setRampDec(double rampDistance, double rampOrientation);
	void setHasObstacle(boolean (*hasObstacle)(void));

	// Getter pour les enchainement de valeurs
	boolean getTrajetAtteint();
	boolean getTrajetEnApproche();

	// Pour la modification de la vitesse a chaud
	void setVitesse(word vDistance, word vOrientation);

private:
	// FIXME : Ces coëficient doivent dépendre de la vitesse courrante du robot, car en 10ms a forte vitesse on peut dépasser.
	#define FENETRE_EN_APPROCHE_DISTANCE	640 	// +- 320 pulse pour la reception de la nouvelle position -> 2 cm
	#define FENETRE_EN_APPROCHE_ORIENTATION 228		// +- 56,8 pulse pour la reception de la nouvelle position -> 5°

	Odometrie odom;
	Encodeurs enc;
	ConsignePolaire consignePolaire;
	Asservissement asserv;
	SD21Motors moteurs;

	RobotConsigne consigneTable;

	boolean (*hasObstacle)(void);

	unsigned long timePrec;
	unsigned long time;

	double fenetreArretDistance;
	double fenetreArretOrientation;

	boolean trajetAtteint;
	boolean trajetEnApproche;

	void calculConsigne();
};

#endif /* ROBOTMANAGER_H_ */
