/*
 * Asservissement.cpp
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#include "Asservissement.h"
#include "../../filters/PID_v1.h"
#include "../../filters/QuadRamp.h"

/*
 * Constructeur
 */
Asservissement::Asservissement() {
	this->sampleTime = 100;
	setup();
}

/*
 * Constructeur
 */
Asservissement::Asservissement(int sampleTime) {
	this->sampleTime = sampleTime;
	setup();
}

// -------------------------------------------------------------- //
// ----------------------- BUSINESS METHODS --------------------- //
// -------------------------------------------------------------- //

/*
 * Cette méthode initialise l'asservissement.
 * Les valeurs peuvent être modifié par les accesseurs.
 */
void Asservissement::setup() {
	// Variable
	inputDistance = inputOrientation = 0;
	outputDistance = outputOrientation = 0;
	consigneDistance = consigneOrientation = 0;

	// Initialisation des élements de l'asservissement
	pidDistance = PID(&inputDistance, &outputDistance, &consigneDistance, 1, 0, 0, DIRECT);
	pidOrientation = PID(&inputOrientation, &outputOrientation, &consigneOrientation, 1, 0, 0, DIRECT);
	filterDistance = QuadRamp(sampleTime, 100, 100);
	filterOrientation = QuadRamp(sampleTime, 100, 100);

	pidDistance.SetSampleTime(sampleTime);
	pidOrientation.SetSampleTime(sampleTime);

	// Définitions des bornes pour la compatibilité avec la carte MD22
	pidDistance.SetOutputLimits(-128, 127);
	pidOrientation.SetOutputLimits(-128, 127);
}

void Asservissement::process(Encodeurs * enc, ConsignePolaire * cp) {
	// Récupération des valeurs réel
	inputDistance = enc->getDistance();
	inputOrientation = enc->getOrientation();

	// Application du filtre pour la génération du profil trapézoidale
	cp->setSetPointDistance(filterDistance.filter(cp->getVitesseDistance(), cp->getConsigneDistance(), enc->getDistance(), cp->isFreinEnable()));
	cp->setSetPointOrientation(filterOrientation.filter(cp->getVitesseOrientation(), cp->getConsigneOrientation(), enc->getOrientation(), cp->isFreinEnable()));

	// Définition des consignes
	consigneDistance = cp->getSetPointDistance();
	consigneOrientation = cp->getSetPointOrientation();

	// Calcul du filtres PID
	pidDistance.Compute();
	pidOrientation.Compute();

	// Envoi des consignes aux moteurs
	cp->setCmdDroit(outputDistance + outputOrientation);
	cp->setCmdGauche(outputDistance - outputOrientation);

#ifdef DEBUG_MODE
	Serial.print("\tCMD Asserv : D -> ");
	Serial.print(cp->getCmdDroit());
	Serial.print(" ; G -> ");
	Serial.print(cp->getCmdGauche());
#endif
}

// -------------------------------------------------------------- //
// ---------------------- GETTERS / SETTERS --------------------- //
// -------------------------------------------------------------- //

void Asservissement::setSampleTime(unsigned int sampleTime) {
	this->sampleTime = sampleTime;
	pidDistance.SetSampleTime(sampleTime);
	pidOrientation.SetSampleTime(sampleTime);
}

unsigned int Asservissement::getSampleTime() {
	return this->sampleTime;
}

void Asservissement::setPIDDistance(double kp, double ki, double kd) {
	pidDistance.SetTunings(kp, ki, kd);
}

void Asservissement::setPIDOrientation(double kp, double ki, double kd) {
	pidOrientation.SetTunings(kp, ki, kd);
}

void Asservissement::setRampAcc(double rampDistance, double rampOrientation) {
	filterDistance.setRampAcc(rampDistance);
	filterOrientation.setRampDec(rampOrientation);
}

void Asservissement::setRampDec(double rampDistance, double rampOrientation) {
	filterDistance.setRampDec(rampDistance);
	filterOrientation.setRampDec(rampOrientation);
}
