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
	setPointDistance = 0;
	setPointOrientation = 0;
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

void ConsignePolaire::setConsigneDistance(double value) {
	consigneDistance = value;
}
double ConsignePolaire::getConsigneDistance() {
	return consigneDistance;
}

void ConsignePolaire::setSetPointDistance(double value) {
	setPointDistance = value;
}
double ConsignePolaire::getSetPointDistance() {
	return setPointDistance;
}

void ConsignePolaire::setVitesseDistance(double value) {
	vitesseDistance = value;
}
double ConsignePolaire::getVitesseDistance() {
	return vitesseDistance;
}

void ConsignePolaire::setConsigneOrientation(double value) {
	consigneOrientation = value;
}
double ConsignePolaire::getConsigneOrientation() {
	return consigneOrientation;
}

void ConsignePolaire::setSetPointOrientation(double value) {
	setPointOrientation = value;
}
double ConsignePolaire::getSetPointOrientation() {
	return setPointOrientation;
}

void ConsignePolaire::setCmdDroit(int value) {
	cmdDroit = value;
}
int ConsignePolaire::getCmdDroit() {
	return cmdDroit;
}

void ConsignePolaire::setCmdGauche(int value) {
	cmdGauche = value;
}
int ConsignePolaire::getCmdGauche() {
	return cmdGauche;
}

void ConsignePolaire::setVitesseOrientation(double value) {
	vitesseOrientation = value;
}
double ConsignePolaire::getVitesseOrientation() {
	return vitesseOrientation;
}

boolean ConsignePolaire::isFreinEnable() {
	return frein;
}
