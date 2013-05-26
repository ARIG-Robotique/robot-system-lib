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
	moteurs = SD21Motors();

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
	stop();
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
		if (consignePolaire.getFrein()
				&& abs(consignePolaire.getConsigneDistance()) < FENETRE_ARRET_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_ARRET_ORIENTATION) {

			// Notification que le trajet est atteint.
			trajetAtteint = true;
		}

		if (abs(consignePolaire.getConsigneDistance()) < FENETRE_EN_APPROCHE_DISTANCE
				&& abs(consignePolaire.getConsigneOrientation()) < FENETRE_EN_APPROCHE_ORIENTATION) {

			// Notification que le point de passage est atteint, envoi de la position suivante requis
			if (!consignePolaire.getFrein()) {
				trajetEnApproche = true;
			}

			// Modification du type de consigne pour la stabilisation
			consigneTable.setType(CONSIGNE_POLAIRE);
		}

#ifdef DEBUG_MODE
		Serial.print(";");Serial.print(trajetEnApproche, DEC);
		Serial.print(";");Serial.print(trajetAtteint, DEC);
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

		Serial.print(";ODOM");
		// Calcul en fonction de l'odométrie
		double dX = consigneTable.getPosition().getX() - odom.getPosition().getX();
		double dY = consigneTable.getPosition().getY() - odom.getPosition().getY();

		long alpha = Conv.radToPulse(atan2(Conv.pulseToRad(dY), Conv.pulseToRad(dX)));

		// Ajustement a PI
		long consigneOrientation = alpha - odom.getPosition().getAngle();
		if (consigneOrientation > Conv.getPiPulse()) {
			consigneOrientation = consigneOrientation - Conv.get2PiPulse();
		} else if (consigneOrientation < -Conv.getPiPulse()) {
			consigneOrientation = consigneOrientation + Conv.get2PiPulse();
		}

		// Sauvegarde des consignes
		consignePolaire.setConsigneDistance(sqrt(pow(dX, 2) + pow(dY, 2)));
		consignePolaire.setConsigneOrientation(consigneOrientation);

	} else {
		Serial.print(";POLAIRE");
		// Calcul par différence vis a vis de la valeur codeur.
		// Cela permet d'éviter que le robot fasse une spirale du plus bel effet pour le maintient en position.
		consignePolaire.setConsigneDistance(consignePolaire.getConsigneDistance() - enc.getDistance());
		consignePolaire.setConsigneOrientation(consignePolaire.getConsigneOrientation() - enc.getOrientation());
	}

#ifdef DEBUG_MODE
	Serial.print(";");Serial.print(Conv.pulseToMm(consignePolaire.getConsigneDistance()));
	Serial.print(";");Serial.print(Conv.pulseToDeg(consignePolaire.getConsigneOrientation()));
#endif
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

/*
 * Méthode pour passer une consigne d'asservissement
 */
void RobotManager::setConsigneTable(RobotConsigne rc) {
	// Sauvegarde des consignes
	consigneTable = rc;
	if (rc.getType() == CONSIGNE_POLAIRE) {
		consignePolaire = rc.getConsignePolaire();
	}

	// Réinitialisation des infos de trajet
	trajetAtteint = false;
	trajetEnApproche = false;
}

/*
 * Cette méthode permet de mettre à jour la position actuel.
 * Elle est utilisé lors de l'initialisation ou en cas de recalage.
 */
void RobotManager::setPosition(double x, double y, double angle) {
	odom.initOdometrie(x, y, angle);
}

/*
 * Accesseur pour la position courante du robot.
 */
RobotPosition RobotManager::getPosition() {
	return odom.getPosition();
}

/*
 * Mutateur pour spécifier le temps d'asservissement.
 */
void RobotManager::setSampleTime(int sampleTime) {
	asserv.setSampleTimeMs(sampleTime);
}

/*
 * Configuration du PID pour l'asservissement en distance
 */
void RobotManager::setPIDDistance(double kp, double ki, double kd) {
	asserv.setPIDDistance(kp, ki, kd);
}

/*
 * Configuration du PID pour l'asservissement en orientation
 */
void RobotManager::setPIDOrientation(double kp, double ki, double kd) {
	asserv.setPIDOrientation(kp, ki, kd);
}

/*
 * Configuration des rampes d'acceleration
 */
void RobotManager::setRampAcc(double rampDistance, double rampOrientation) {
	asserv.setRampAcc(rampDistance, rampOrientation);
}

/*
 * Configuration des rampes de décéleration
 */
void RobotManager::setRampDec(double rampDistance, double rampOrientation) {
	asserv.setRampDec(rampDistance, rampOrientation);
}

/*
 * Mutateur pour préciser la fonction permettant d'effectuer la détéction d'obstacle pour l'evittement.
 * Il s'agit d'un pointeur de fonction ayant la signature suivante :
 *
 * 		boolean maFonction();
 *
 */
void RobotManager::setHasObstacle(boolean (*hasObstacle)(void)){
	this->hasObstacle = hasObstacle;
}

/*
 * Accesseur pour savoir si la position demandé est atteinte
 */
boolean RobotManager::getTrajetAtteint() {
	return trajetAtteint;
}

/*
 * Accesseur pour savoir si la position demandé est en approche.
 * Est utilisé pour l'enchainement de point de passage.
 */
boolean RobotManager::getTrajetEnApproche() {
	return trajetEnApproche;
}

/*
 * Mutateur pour spécifier la vitesse de déplacement du robot
 */
void RobotManager::setVitesse(word vDistance, word vOrientation) {
	consignePolaire.setVitesseDistance(vDistance);
	consignePolaire.setVitesseOrientation(vOrientation);
}
