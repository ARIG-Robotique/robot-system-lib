/*
 * RobotManager.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "RobotManager.h"
#include "utils/Convertion.h"

RobotManager::RobotManager() {
	odom = Odometrie();
	enc = Encodeurs();
	consigne = ConsignePolaire();
	asserv = Asservissement();
	moteurs = MD22();

	timePrec = time = 0;
	trajetAtteint = false;
	trajetEnApproche = false;
}

/* ------------------------------------------------------------------ */
/* ------------------------ BUSINESS METHODS ------------------------ */
/* ------------------------------------------------------------------ */

/*
 * Fonction permettant d'initialiser les composants externe pour le fonctionnement
 */
void RobotManager::init() {
	// Initialisation des cartes codeurs
#ifdef DEBUG_MODE
	enc.printVersion();
#endif
	resetEncodeurs();

	// Initialisation du contrôle moteurs
#ifdef DEBUG_MODE
	moteurs.printVersion();
#endif
	moteurs.init();
}

/*
 * Commande de reset des valeurs codeurs
 */
void RobotManager::resetEncodeurs() {
	enc.reset();
}

/*
 * Fonction permettant de gérer l'arret des actionneur du manageur
 */
void RobotManager::stop() {
	moteurs.stopAll();
}

/*
 * Cette méthode permet de réaliser les fonctions lié aux déplacements.
 * Le schéduling est assuré par la méthode elle même. De ce fait elle peut
 * être appélé depuis la loop principale.
 */
void RobotManager::process() {
	time = millis();
	if ((time - timePrec) >= asserv.getSampleTimeMs()) {
		timePrec = time;

		// 1. Calcul de la position du robot
		enc.lectureValeurs();
		odom.calculPosition(&enc);

		// 2. Calcul des consignes
		calculConsigne();

		// 3. Asservissement sur les consignes
		asserv.process(&enc, &consigne);

		// 4. Envoi aux moteurs
		moteurs.generateMouvement(consigne.getCmdGauche(), consigne.getCmdGauche());

		// 5. Gestion des flags pour le séquencement du calcul de la position
		trajetAtteint = false;
		trajetEnApproche = false;
		if (consigne.isFreinEnable()
				&& abs(consigne.getConsigneDistance()) < FENETRE_ARRET_DISTANCE
				&& abs(consigne.getConsigneOrientation()) < FENETRE_ARRET_ORIENTATION) {

			trajetAtteint = true;

		} else if (!consigne.isFreinEnable()
				&& abs(consigne.getConsigneDistance()) < FENETRE_EN_APPROCHE_DISTANCE
				&& abs(consigne.getConsigneOrientation()) < FENETRE_EN_APPROCHE_ORIENTATION) {

			trajetEnApproche = true;
		}

#ifdef DEBUG_MODE
		Serial.println(';');
#endif
	}
}

/*
 * Calcul des consigne d'asservissement
 * -> a : Gestion en fonction de l'odométrie
 * -> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
 */
void RobotManager::calculConsigne() {
	if (!trajetAtteint) {
		// Calcul en fonction de l'odométrie
		double dX = consigneTable.getPosition().getX() - odom.getPosition().getX();
		double dY = consigneTable.getPosition().getY() - odom.getPosition().getY();

		long int alpha = Conv.radToPulse(atan2(Conv.pulseToRad(dY), Conv.pulseToRad(dX)));

		consigne.setConsigneDistance(sqrt(pow(dX, 2) + pow(dY, 2)));
		consigne.setConsigneOrientation(alpha - odom.getPosition().getAngle());

	} else {
		// Calcul par différence vis a vis de la valeur codeur.
		// Cela permet d'éviter que le robot fasse un spirale du plus bel effet pour le maintient en position.
		consigne.setConsigneDistance(consigne.getConsigneDistance() - enc.getDistance());
		consigne.setConsigneOrientation(consigne.getConsigneOrientation() - enc.getOrientation());
	}

	// Gestion du frein pour la détection des approches et trajet atteint
	if (consigneTable.getFrein()) {
		consigne.enableFrein();
	} else {
		consigne.disableFrein();
	}

#ifdef DEBUG_MODE
	Serial.print("\tCalc. Cons. F : ");
	Serial.print(consigne.isFreinEnable());
	Serial.print(" ; D : ");
	Serial.print(Conv.pulseToMm(consigne.getConsigneDistance()));
	Serial.print(" ; A : ");
	Serial.print((double) Conv.pulseToDeg(consigne.getConsigneOrientation()));
#endif

	// TODO : Définition de la vitesse demandé
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

void RobotManager::setConsigneTable(RobotConsigne rc) {
	consigneTable = rc;
}

void RobotManager::setSampleTime(int sampleTime) {
	asserv.setSampleTimeMs(sampleTime);
}

void RobotManager::setPIDDistance(double kp, double ki, double kd) {
	asserv.setPIDDistance(kp, ki, kd);
}

void RobotManager::setPIDOrientation(double kp, double ki, double kd) {
	asserv.setPIDOrientation(kp, ki, kd);
}

void RobotManager::setRampAcc(double rampDistance, double rampOrientation) {
	asserv.setRampAcc(rampDistance, rampOrientation);
}

void RobotManager::setRampDec(double rampDistance, double rampOrientation) {
	asserv.setRampDec(rampDistance, rampOrientation);
}
