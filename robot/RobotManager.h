/*
 * RobotManager.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTMANAGER_H_
#define ROBOTMANAGER_H_

#include <Arduino.h>

class RobotManager {
public:
	RobotManager();
	virtual ~RobotManager();

	void process();
};

#endif /* ROBOTMANAGER_H_ */
