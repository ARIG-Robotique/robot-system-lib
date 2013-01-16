/*
 * RobotManager.cpp
 *
 *  Created on: 22 d�c. 2012
 *      Author: mythril
 */

#include "RobotManager.h"

// Pre instanciate (en variable global, c'est mal mais le SDK Arduino marche comme �a).
RobotManager RM = RobotManager();

RobotManager::RobotManager() {
	odom = Odometrie();
	enc = Encodeurs();
	consigne = ConsignePolaire();
	asserv = Asservissement();
}

RobotManager::~RobotManager() {
}

/*
 * Cette m�thode permet de r�aliser les fonctions li� aux d�placements.
 * Elle doit �tre sch�duler via un timer toutes les x ms
 */
void RobotManager::process() {
	// 1. Calcul de la position du robot
	enc.lectureValeurs();
	odom.calculPosition(&enc);

	// 2. Calcul des consignes

	// 3. Asservissement sur les consignes
}
