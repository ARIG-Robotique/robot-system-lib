/*
 * RobotPosition.cpp
 *
 *  Created on: 22 dŽc. 2012
 *      Author: mythril
 */

#include "RobotPosition.h"

RobotPosition::RobotPosition() {
	setX(0);
	setY(0);
	setAngle(0);
}

// -------------------------------------------------------- //
// --------------------- BUSINESS ------------------------- //
// -------------------------------------------------------- //

/* Mise a jour de la position du robot */
void RobotPosition::updatePosition(double x, double y, int angle) {
	setX(x);
	setY(y);
	setAngle(angle);
}

// -------------------------------------------------------- //
// ----------------- GETTER / SETTER ---------------------- //
// -------------------------------------------------------- //

int RobotPosition::getAngle() {
	return angle;
}

void RobotPosition::setAngle(int angle) {
	this->angle = angle;
}

double RobotPosition::getX() {
	return x;
}

void RobotPosition::setX(double x) {
	this->x = x;
}

double RobotPosition::getY() {
	return y;
}

void RobotPosition::setY(double y) {
	this->y = y;
}
