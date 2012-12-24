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

using namespace utils;

class Odometrie {
public:
	Odometrie();
	virtual ~Odometrie();

	void initOdometrie(double x, double y, int angle);
	void calculPosition(Encodeurs * enc);
	RobotPosition getPosition();
};

#endif /* ODOMETRIE_H_ */
