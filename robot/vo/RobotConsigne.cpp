/*
 * RobotConsigne.cpp
 *
 *  Created on: 16 avr. 2013
 *      Author: mythril
 */

#include "RobotConsigne.h"

/*
 * Constructeur
 */
RobotConsigne::RobotConsigne() {
	position = RobotPosition();
	consignePolaire = ConsignePolaire();
	type = CONSIGNE_POLAIRE;
	consignePolaire.setFrein(true);
}

/*
 * Mutateur pour la récupération de la position de consigne du robot sur la table
 */
void RobotConsigne::setPosition(RobotPosition position) {
	this->position = position;
}
RobotPosition RobotConsigne::getPosition() {
	return position;
}

/*
 * Mutateur pour la récupération de la consigne en polaire sur la table pour avoir des mouvements basique
 */
void RobotConsigne::setConsignePolaire(ConsignePolaire cp) {
	this->consignePolaire = cp;
}
ConsignePolaire RobotConsigne::getConsignePolaire() {
	return consignePolaire;
}

/*
 * Mutateur pour définir le type de consigne
 */
void RobotConsigne::setType(char type) {
	this->type = type;
}

/*
 * Accesseur pour récupérer le type de consigne
 */
char RobotConsigne::getType() {
	return type;
}

/*
 * Wraper de config du frein
 */
void RobotConsigne::enableFrein() {
	consignePolaire.setFrein(true);
}

void RobotConsigne::disableFrein() {
	consignePolaire.setFrein(false);
}

/*
 * Accesseur pour récupérer la valeur du frein
 */
boolean RobotConsigne::getFrein() {
	return consignePolaire.getFrein();
}
