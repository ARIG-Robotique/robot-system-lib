/*
 * RobotManager.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

// Value Object
#include "vo/RobotPosition.h"
#include "vo/ConsignePolaire.h"

// Business elements
#include "system/Encodeurs.h"
#include "system/Odometrie.h"
#include "system/Asservissement.h"
#include "system/motors/MD22.h"

class RobotManager {
public:
	RobotManager();

	void init();
	void process();

private:
	Odometrie odom;
	Encodeurs enc;
	ConsignePolaire consigne;
	Asservissement asserv;
	MD22 moteurs;

	void calculConsigne();
};

extern RobotManager RM;

#endif /* ROBOTMANAGER_H_ */
