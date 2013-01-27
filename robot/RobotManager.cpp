/*
 * RobotManager.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "RobotManager.h"

RobotManager::RobotManager() {
	odom = Odometrie();
	enc = Encodeurs();
	consigne = ConsignePolaire();
	asserv = Asservissement();
}

/* ------------------------------------------------------------------ */
/* ------------------------ BUSINESS METHODS ------------------------ */
/* ------------------------------------------------------------------ */

/*
 * Cette méthode permet de réaliser les fonctions lié aux déplacements.
 * Elle doit être schéduler via un timer toutes les x ms
 */
void RobotManager::process() {
	// 1. Calcul de la position du robot
	enc.lectureValeurs();
	odom.calculPosition(&enc);

	// 2. Calcul des consignes

	// 3. Asservissement sur les consignes
	asserv.process(&enc, &consigne);

	// 4. Envoi aux moteurs
}
