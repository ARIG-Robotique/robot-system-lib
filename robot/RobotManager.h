/*
 * RobotManager.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

#include <Arduino.h>

// Value Object
#include "vo/RobotPosition.h"

// Business elements
#include "system/Encodeurs.h"
#include "system/Odometrie.h"

class RobotManager {
public:
	RobotManager();
	virtual ~RobotManager();

	void process();

private:
	RobotPosition positionRobot;
	Odometrie odometrie;


};

#endif /* ROBOTMANAGER_H_ */
