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
	consignePolaire = ConsignePolaire();
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
		asserv.process(enc, consignePolaire);

		// 4. Envoi aux moteurs
		moteurs.generateMouvement(consignePolaire.getCmdGauche(), consignePolaire.getCmdDroit());

		// 5. Gestion des flags pour le séquencement du calcul de la position
		trajetAtteint = false;
		trajetEnApproche = false;
		if (consignePolaire.getFrein()
				&& abs(consignePolaire.getConsigneDistance()) < FENETRE_ARRET_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_ARRET_ORIENTATION) {

			// Notification que le trajet est atteint.
			trajetAtteint = true;

			// TODO : Voir si il faut changer les param PID pour la stabilisation

		} else if (consignePolaire.getFrein()
				&& abs(consignePolaire.getConsigneDistance()) < FENETRE_EN_APPROCHE_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_EN_APPROCHE_ORIENTATION) {

			// Notification que le point de passage est atteint, envoi de la position suivante requis
			trajetEnApproche = true;
		}

#ifdef DEBUG_MODE
		Serial.print(";TrajApp ");Serial.print(trajetEnApproche, DEC);
		Serial.print(";TrajAtt ");Serial.print(trajetAtteint, DEC);
		Serial.println();
#endif
	}
}

/*
 * Calcul des consignes d'asservissement
 * -> a : Gestion en fonction de l'odométrie
 * -> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
 */
void RobotManager::calculConsigne() {
	if (!trajetAtteint && consigneTable.getType() != CONSIGNE_POLAIRE) {
		// Calcul en fonction de l'odométrie
		double dX = consigneTable.getPosition().getX() - odom.getPosition().getX();
		double dY = consigneTable.getPosition().getY() - odom.getPosition().getY();

		long int alpha = Conv.radToPulse(atan2(Conv.pulseToRad(dY), Conv.pulseToRad(dX)));

		consignePolaire.setConsigneDistance(sqrt(pow(dX, 2) + pow(dY, 2)));
		consignePolaire.setConsigneOrientation(alpha - odom.getPosition().getAngle());

	} else {
		// Calcul par différence vis a vis de la valeur codeur.
		// Cela permet d'éviter que le robot fasse une spirale du plus bel effet pour le maintient en position.
		consignePolaire.setConsigneDistance(consignePolaire.getConsigneDistance() - enc.getDistance());
		consignePolaire.setConsigneOrientation(consignePolaire.getConsigneOrientation() - enc.getOrientation());
	}
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

void RobotManager::setConsigneTable(RobotConsigne rc) {
	consigneTable = rc;
	if (rc.getType() == CONSIGNE_POLAIRE) {
		consignePolaire = rc.getConsignePolaire();
	}
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

boolean RobotManager::getTrajetAtteint() {
	return trajetAtteint;
}

boolean RobotManager::getTrajetEnApproche() {
	return trajetEnApproche;
}

void RobotManager::setVitesse(word vDistance, word vOrientation) {
	consignePolaire.setVitesseDistance(vDistance);
	consignePolaire.setVitesseOrientation(vOrientation);
}
