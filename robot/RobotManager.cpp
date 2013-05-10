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

	evittementEnCours = false;
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

		// 3.Gestion de l'evittement, de la reprise, et du cycle continue
		if ((*hasObstacle)() && !evittementEnCours) {
			consigneEvittement = ConsignePolaire();
			consigneEvittement.setVitesseDistance(consignePolaire.getVitesseDistance());
			consigneEvittement.setVitesseOrientation(consignePolaire.getVitesseOrientation());
			consigneEvittement.setConsigneOrientation(consignePolaire.getConsigneOrientation());
			double distArret = Conv.mmToPulse(50);
			if (consignePolaire.getConsigneDistance() > distArret) {
				consigneEvittement.setConsigneDistance(distArret);
			} else {
				consigneEvittement.setConsigneDistance(consignePolaire.getConsigneDistance());
			}

			// 3.1.1. Asservissement sur les consignes
			asserv.process(enc, consigneEvittement);

			// 3.1.2. Envoi aux moteurs
			moteurs.generateMouvement(consigneEvittement.getCmdGauche(), consigneEvittement.getCmdDroit());

			evittementEnCours = true;

		} else if ((*hasObstacle)() && evittementEnCours) {
			consigneEvittement.setConsigneDistance(consigneEvittement.getConsigneDistance() - enc.getDistance());
			consigneEvittement.setConsigneOrientation(consigneEvittement.getConsigneOrientation() - enc.getOrientation());

			// 3.2.1. Asservissement sur les consignes
			asserv.process(enc, consigneEvittement);

			// 3.2.2. Envoi aux moteurs
			moteurs.generateMouvement(consigneEvittement.getCmdGauche(), consigneEvittement.getCmdDroit());

		} else if (!(*hasObstacle)() && evittementEnCours) {
			//asserv.setRampDec(rampDecDistance,rampDecOrientation);
			evittementEnCours = false;

		} else {
			// 3.4.1. Asservissement sur les consignes
			asserv.process(enc, consignePolaire);

			// 3.4.2. Envoi aux moteurs
			moteurs.generateMouvement(consignePolaire.getCmdGauche(), consignePolaire.getCmdDroit());
		}

		// 5. Gestion des flags pour le séquencement du calcul de la position
		trajetAtteint = false;
		trajetEnApproche = false;
		if (consignePolaire.getFrein()
				&& abs(consignePolaire.getConsigneDistance()) < FENETRE_ARRET_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_ARRET_ORIENTATION) {

			// Notification que le trajet est atteint.
			trajetAtteint = true;
			// TODO : Voir si il faut changer les param PID pour la stabilisation

		} else if (!consignePolaire.getFrein()
				&& abs(consignePolaire.getConsigneDistance()) < FENETRE_EN_APPROCHE_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_EN_APPROCHE_ORIENTATION) {

			// Notification que le point de passage est atteint, envoi de la position suivante requis
			trajetEnApproche = true;
		}

#ifdef DEBUG_MODE
		Serial.print(";App ");Serial.print(trajetEnApproche, DEC);
		Serial.print(";Att ");Serial.print(trajetAtteint, DEC);
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
	if (!trajetAtteint && consigneTable.getType() == CONSIGNE_ODOMETRIE) {

		Serial.print(";Calcul ODOM");
		// Calcul en fonction de l'odométrie
		double dX = consigneTable.getPosition().getX() - odom.getPosition().getX();
		double dY = consigneTable.getPosition().getY() - odom.getPosition().getY();

		long int alpha = Conv.radToPulse(atan2(Conv.pulseToRad(dY), Conv.pulseToRad(dX)));

		consignePolaire.setConsigneDistance(sqrt(pow(dX, 2) + pow(dY, 2)));
		consignePolaire.setConsigneOrientation(alpha - odom.getPosition().getAngle());


	} else {
		Serial.print(";Calcul POLAIRE");
		// Calcul par différence vis a vis de la valeur codeur.
		// Cela permet d'éviter que le robot fasse une spirale du plus bel effet pour le maintient en position.
		consignePolaire.setConsigneDistance(consignePolaire.getConsigneDistance() - enc.getDistance());
		consignePolaire.setConsigneOrientation(consignePolaire.getConsigneOrientation() - enc.getOrientation());
	}

	Serial.print(";Cons d ");Serial.print(Conv.pulseToMm(consignePolaire.getConsigneDistance()));
	Serial.print(";Cons o ");Serial.print(Conv.pulseToDeg(consignePolaire.getConsigneOrientation()));
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

void RobotManager::setConsigneTable(RobotConsigne rc) {
	// Réinitialisation des infos de trajet
	trajetAtteint = false;
	trajetEnApproche = false;

	// Sauvegarde des consigne
	consigneTable = rc;
	if (rc.getType() == CONSIGNE_POLAIRE) {
		consignePolaire = rc.getConsignePolaire();
	}

	// Annulation des erreur PID précédentes
	asserv.reset();
}

void RobotManager::setPosition(double x, double y, double angle) {
	odom.initOdometrie(x, y, angle);
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
	rampDecDistance = rampDistance;
	rampDecOrientation = rampOrientation;
}

void RobotManager::setHasObstacle(boolean (*hasObstacle)(void)){
	this->hasObstacle = hasObstacle;
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
