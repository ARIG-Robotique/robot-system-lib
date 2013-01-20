/*
 * Odometrie.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "Odometrie.h"

/*
 * Constructeur
 */
Odometrie::Odometrie() {
	position = RobotPosition();
	position.updatePosition(0, 0, 0);
}

/*
 * Destructeur
 */
Odometrie::~Odometrie() {
}

/*
 * Initialisation de l'odométrie avec une position.
 */
void Odometrie::initOdometrie(double x, double y, int angle) {
	position.updatePosition(x, y, angle);
}

/*
 * Calcul de la position en fonction de la valeurs des codeurs.
 * Ce calcul est effectué avec le postulat que durant le labs de temps écoulé le robot a roulé droit (pas en courbe).
 * On parle donc d'approximation linéaire.
 *
 * /!\ Cette méthode doit être appelé après la lecture des valeurs codeurs toutes les x ms.
 */
void Odometrie::calculPosition(Encodeurs * enc) {
	// Approximation linéaire
	position.setAngle(position.getAngle() + enc->getOrientation());
	long double thetaRad = Conv.pulseToRad(position.getAngle());
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

/*
 * Renvoi la position calculé.
 */
RobotPosition Odometrie::getPosition() {
	return position;
}
