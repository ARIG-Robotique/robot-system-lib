/*
 * RobotConsigne.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: mythril
 */

#include "RobotConsigne.h"

RobotConsigne::RobotConsigne() {
	position = RobotPosition();
	frein = false;
}

RobotPosition RobotConsigne::getPosition() {
	return position;
}

void RobotConsigne::setFrein(boolean val) {
	frein = val;
}

boolean RobotConsigne::getFrein() {
	return frein;
}
