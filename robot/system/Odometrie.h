/*
 * Odometrie.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ODOMETRIE_H_
#define ODOMETRIE_H_

#include <math.h>

#include "Encodeurs.h"
#include "../vo/RobotPosition.h"
#include "../utils/Convertion.h"

class Odometrie {
public:
	Odometrie();

	void initOdometrie(double x, double y, int angle);
	void calculPosition(Encodeurs *);
	RobotPosition getPosition();

	int getPiPulse();
	int get2PiPulse();
private:
	RobotPosition position;

	int piPulse;
	int pi2Pulse;
};

#endif /* ODOMETRIE_H_ */
