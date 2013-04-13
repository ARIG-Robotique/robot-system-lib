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
}

/* ------------------------------------------------------------------ */
/* ------------------------ BUSINESS METHODS ------------------------ */
/* ------------------------------------------------------------------ */

/*
 * Cette mŽthode permet de rŽaliser les fonctions liŽ aux dŽplacements.
 * Elle doit tre schŽduler via un timer toutes les x ms
 */
void RobotManager::process() {
	// 1. Calcul de la position du robot
	enc.lectureValeurs();
	odom.calculPosition(&enc);

	// 2. Calcul des consignes
	// 	-> a : Gestion en fonction de l'odomŽtrie
	//	-> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
	// TODO

	// 3. Asservissement sur les consignes
	asserv.process(&enc, &consigne);

	// 4. Envoi aux moteurs
	moteurs.generateMouvement(consigne.getCmdGauche(), consigne.getCmdGauche());
}
