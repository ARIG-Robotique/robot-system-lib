/*
 * RobotManager.cpp
 *
 *  Created on: 22 dŽc. 2012
 *      Author: mythril
 */

#include "RobotManager.h"

RobotManager::RobotManager() {
	odom = Odometrie();
	enc = Encodeurs();
	consigne = ConsignePolaire();
	asserv = Asservissement();
	moteurs = MD22();

	timePrec = time = 0;
}

/* ------------------------------------------------------------------ */
/* ------------------------ BUSINESS METHODS ------------------------ */
/* ------------------------------------------------------------------ */

/*
 * Fonction permettant d'initialiser les composants externe pour le fonctionnement
 */
void RobotManager::init() {
	// Initialisation des cartes codeurs
	enc.printVersion();
	enc.reset();

	// Initialisation du contr™le moteurs
	moteurs.printVersion();
	moteurs.init();
}

/*
 * Fonction permettant de gŽrer l'arret des actionneur du manageur
 */
void RobotManager::stop() {
	moteurs.stopAll();
}

/*
 * Cette mŽthode permet de rŽaliser les fonctions liŽ aux dŽplacements.
 * Le schŽduling est assurŽ par la mŽthode elle mme. De ce fait elle peut
 * tre appŽlŽ depuis la loop principale.
 */
void RobotManager::process() {
	time = millis();
	if ((time - timePrec) >= asserv.getSampleTime()) {
		timePrec = time;
		Serial.print("RM PROCESS : ");
		Serial.println(timePrec, DEC);

		moteurs.generateMouvement(20, 20);
		/*
		// 1. Calcul de la position du robot
		enc.lectureValeurs();
		odom.calculPosition(&enc);

		// 2. Calcul des consignes
		// 	-> a : Gestion en fonction de l'odomŽtrie
		//	-> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
		//  TODO : Algorithme de calcul des consigne

		// 3. Asservissement sur les consignes
		asserv.process(&enc, &consigne);

		// 4. Envoi aux moteurs
		moteurs.generateMouvement(consigne.getCmdGauche(), consigne.getCmdGauche());
		*/
	}
}

/* ------------------------------------------------------------------ */
/* ------------------------ GETTERS / SETTERS ----------------------- */
/* ------------------------------------------------------------------ */

void RobotManager::setSampleTime(int sampleTime) {
	asserv.setSampleTime(sampleTime);
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
