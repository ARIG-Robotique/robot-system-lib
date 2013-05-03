/*
 * ConsignePolaire.cpp
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#include "ConsignePolaire.h"

ConsignePolaire::ConsignePolaire() {
	consigneDistance = 0;
	consigneOrientation = 0;
	vitesseDistance = 100;
	vitesseOrientation = 100;
	cmdDroit = 0;
	cmdGauche = 0;
	enableFrein();
}

void ConsignePolaire::enableFrein() {
	frein = true;
}
void ConsignePolaire::disableFrein() {
	frein = false;
}

// -------------------------------------------------------- //
// ----------------- GETTER / SETTER ---------------------- //
// -------------------------------------------------------- //

void ConsignePolaire::setConsigneDistance(long value) {
	consigneDistance = value;
}
long ConsignePolaire::getConsigneDistance() {
	return consigneDistance;
}

void ConsignePolaire::setVitesseDistance(word value) {
	vitesseDistance = value;
}
word ConsignePolaire::getVitesseDistance() {
	return vitesseDistance;
}

void ConsignePolaire::setConsigneOrientation(long value) {
	consigneOrientation = value;
}
long ConsignePolaire::getConsigneOrientation() {
	return consigneOrientation;
}

void ConsignePolaire::setCmdDroit(char value) {
	cmdDroit = value;
}
char ConsignePolaire::getCmdDroit() {
	return cmdDroit;
}

void ConsignePolaire::setCmdGauche(char value) {
	cmdGauche = value;
}
char ConsignePolaire::getCmdGauche() {
	return cmdGauche;
}

void ConsignePolaire::setVitesseOrientation(word value) {
	vitesseOrientation = value;
}
word ConsignePolaire::getVitesseOrientation() {
	return vitesseOrientation;
}

boolean ConsignePolaire::isFreinEnable() {
	return frein;
}
