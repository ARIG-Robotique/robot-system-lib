/*
 * Asservissement.cpp
 *
 *  Created on: 26 dŽc. 2012
 *      Author: mythril
 */

#include "Asservissement.h"
#include "../../filters/PID_v1.h"
#include "../../filters/QuadRamp.h"

Asservissement::Asservissement(int sampleTime) {
	// Variable
	inputDistance = inputOrientation = 0;
	outputDistance = outputOrientation = 0;
	consigneDistance = consigneOrientation = 0;

	this->sampleTime = sampleTime;

	// Initialisation des Žlements de l'asservissement
	motors = MD22Moteurs();
	pidDistance = PID(&inputDistance, &outputDistance, &consigneDistance, 1, 0, 0, DIRECT);
	pidOrientation = PID(&inputOrientation, &outputOrientation, &consigneOrientation, 1, 0, 0, DIRECT);
	filterDistance = QuadRamp(sampleTime, 100, 100);
	filterOrientation = QuadRamp(sampleTime, 100, 100);

	pidDistance.SetSampleTime(sampleTime);
	pidOrientation.SetSampleTime(sampleTime);

	// DŽfinitions des bornes pour la compatibilitŽ avec la carte MD22
	pidDistance.SetOutputLimits(-128, 127);
	pidOrientation.SetOutputLimits(-128, 127);
}

Asservissement::~Asservissement() {
}

// -------------------------------------------------------------- //
// ----------------------- BUSINESS METHODS --------------------- //
// -------------------------------------------------------------- //

void Asservissement::process(Encodeurs * enc, ConsignePolaire * cp) {
	// RŽcupŽration des valeurs rŽel
	inputDistance = enc->getDistance();
	inputOrientation = enc->getOrientation();

	// Application du filtre pour la gŽnŽration du profil trapŽzoidale
	cp->setSetPointDistance(filterDistance.filter(cp->getVitesseDistance(), cp->getConsigneDistance(), enc->getDistance(), cp->isFreinEnable()));
	cp->setSetPointOrientation(filterOrientation.filter(cp->getVitesseOrientation(), cp->getConsigneOrientation(), enc->getOrientation(), cp->isFreinEnable()));

	// DŽfinition des consignes
	consigneDistance = cp->getSetPointDistance();
	consigneOrientation = cp->getSetPointOrientation();

	// Calcul du filtres PID
	pidDistance.Compute();
	pidOrientation.Compute();

	// Envoi des consignes aux moteurs
	int cmdDroit = outputDistance + outputOrientation;
	int cmdGauche = outputDistance - outputOrientation;
	motors.generateMouvement(cmdGauche, cmdDroit);
}

// -------------------------------------------------------------- //
// ---------------------- GETTERS / SETTERS --------------------- //
// -------------------------------------------------------------- //

void Asservissement::setSampleTime(int sampleTime) {
	this->sampleTime = sampleTime;
	pidDistance.SetSampleTime(sampleTime);
	pidOrientation.SetSampleTime(sampleTime);
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
