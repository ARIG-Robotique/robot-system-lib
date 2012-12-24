/*
 * Odometrie.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "Odometrie.h"

RobotPosition position;

Odometrie::Odometrie() {
	position.updatePosition(0, 0, 0);
}

Odometrie::~Odometrie() {
}

void Odometrie::initOdometrie(double x, double y, int angle) {
	position.updatePosition(x, y, angle);
}

void Odometrie::calculPosition(Encodeurs * enc) {
	// Approximation linéaire
	position.setAngle(position.getAngle() + enc->getOrientation());
	long double thetaRad = Convertion.pulseToRad(position.getAngle());
	double dX = enc->getDistance() * cos(thetaRad);
	double dY = enc->getDistance() * sin(thetaRad);
	position.setX(position.getX() + dX);
	position.setY(position.getY() + dY);

	// Approximation circulaire (pas testé)
	/*long double r = encodeurs.nbEncocheDeltaDistance * mmToPulse(ENTRAXE) / (encodeurs.nbEncocheDeltaOrientation * 2);
	long double arcAngle = 2 * encodeurs.nbEncocheDeltaOrientation / (mmToPulse(ENTRAXE));
	positionCourrante.x += r * (-sin(positionCourrante.theta) + sin(positionCourrante.theta + arcAngle));
	positionCourrante.y += r * (cos(positionCourrante.theta) - cos(positionCourrante.theta + arcAngle));
	positionCourrante.theta += arcAngle;*/
}

RobotPosition Odometrie::getPosition() {
	return position;
}
