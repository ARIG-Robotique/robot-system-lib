/*
 * RobotManager.cpp
 *
 *  Created on: 22 d�c. 2012
 *      Author: mythril
 */

#include "RobotManager.h"

// Pre instanciate
RobotManager RM = RobotManager();

RobotManager::RobotManager() {
	odom = Odometrie();
	enc = Encodeurs();
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
