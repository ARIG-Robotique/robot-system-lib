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

class RobotManager {
public:
	RobotManager();
	virtual ~RobotManager();

	void process();

private:
	Odometrie odom;
	Encodeurs enc;
	ConsignePolaire consigne;
	Asservissement asserv;

	void calculConsigne();
};

extern RobotManager RM;

#endif /* ROBOTMANAGER_H_ */
