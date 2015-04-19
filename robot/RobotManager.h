/*
 * RobotManager.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

#include "../common.h"
#include "../utils/Convertion.h"

// Value Object
#include "vo/RobotConsigne.h"
#include "vo/ConsignePolaire.h"

// Business elements
#include "system/Odometrie.h"
#include "system/AsservissementPolaire.h"
#include "system/motors/AbstractPropulsionMotors.h"
#include "system/encoders/AbstractEncodeurs.h"

class RobotManager {
public:
	RobotManager();

	void init();
	void resetEncodeurs();
	void process();
	void stop();

	void setPosition(double x, double y, double angle);
	RobotPosition getPosition();

	// Configuration de l'asservissement
	void setSampleTime(int sampleTime);
	void setPIDDistance(double kp, double ki, double kd);
	void setPIDOrientation(double kp, double ki, double kd);
	void setRampAcc(double rampDistance, double rampOrientation);
	void setRampDec(double rampDistance, double rampOrientation);
	void setVitesse(word vDistance, word vOrientation);

	// Configuration des implémentations pour le manager
	void setMotorsImpl(AbstractPropulsionMotors * impl);
	void setEncodeursImpl(AbstractEncodeurs * impl);

	// Pointeur de fonction pour assurer la detection d'obstacle proche
	void setHasObstacle(boolean (*hasObstacle)(void));

	// Méthode de déplacement
	void gotoPointMM(double x, double y, boolean frein);
	void gotoOrientationDeg(double angle);
	void alignFrontTo(double x, double y);
	void alignBackTo(double x, double y);
	void avanceMM(double distance);
	void reculeMM(double distance);
	void tourneDeg(double angle);
	void followLine(double x1, double y1, double x2, double y2);
	void turnAround(double x, double y, double r);

	// Getter pour les enchainement de valeurs
	boolean getTrajetAtteint();
	boolean getTrajetEnApproche();

private:
	RobotConsigne consigneTable;
	Odometrie odom;
	AsservissementPolaire asserv;

	AbstractPropulsionMotors * moteurs;
	AbstractEncodeurs * enc;

	boolean (*hasObstacle)(void);

	unsigned long timePrec;
	unsigned long time;

	double fenetreArretDistance;
	double fenetreArretOrientation;

	double startAngle;

	boolean trajetAtteint;
	boolean trajetEnApproche;
	boolean evittementEnCours;

	void calculConsigne();
	void gestionFlags();
	double calculAngleConsigne(double dX, double dY);
	double calculDistanceConsigne(double dX, double dY);

	void prepareNextMouvement();
};

#endif /* ROBOTMANAGER_H_ */
