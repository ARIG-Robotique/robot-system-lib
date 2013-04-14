/*
 * RobotManager.cpp
 *
 *  Created on: 22 d�c. 2012
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
 * Fonction permettant d'initialiser les composants externe pour le fonctionnement
 */
void RobotManager::init() {
	// Initialisation des cartes codeurs
	enc.reset();

	// Initialisation du contr�le moteurs
	moteurs.init();
}

/*
 * Cette m�thode permet de r�aliser les fonctions li� aux d�placements.
 * Le sch�duling est assur� par la m�thode elle m�me. De ce fait elle peut
 * �tre app�l� depuis la loop principale.
 */
void RobotManager::process() {
	// TODO : Ajouter le sch�duling avec millis()
	if (true) {
		// 1. Calcul de la position du robot
		enc.lectureValeurs();
		odom.calculPosition(&enc);

		// 2. Calcul des consignes
		// 	-> a : Gestion en fonction de l'odom�trie
		//	-> b : Si dans fenetre d'approche : consigne(n) = consigne(n-1) - d(position)
		//  TODO : Algorithme de calcul des consigne

		// 3. Asservissement sur les consignes
		asserv.process(&enc, &consigne);

		// 4. Envoi aux moteurs
		moteurs.generateMouvement(consigne.getCmdGauche(), consigne.getCmdGauche());
	}
}
