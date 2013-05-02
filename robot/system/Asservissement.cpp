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
	this->sampleTime = 10;
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
	setPointDistance = setPointOrientation = 0;

	// Initialisation des élements de l'asservissement
	pidDistance = PID(&inputDistance, &outputDistance, &setPointDistance, 1, 0, 0, DIRECT);
	pidDistance.SetSampleTime(sampleTime);
	pidDistance.SetOutputLimits(-128, 127);
	pidDistance.SetMode(AUTOMATIC);

	pidOrientation = PID(&inputOrientation, &outputOrientation, &setPointOrientation, 1, 0, 0, DIRECT);
	pidOrientation.SetSampleTime(sampleTime);
	pidOrientation.SetOutputLimits(-128, 127);
	pidOrientation.SetMode(AUTOMATIC);

	// Configuration du filtre pour le profil trapézoïdale
	filterDistance = QuadRamp(sampleTime, 100, 100);
	filterOrientation = QuadRamp(sampleTime, 100, 100);
}

void Asservissement::process(Encodeurs * enc, ConsignePolaire * cp) {
	// Récupération des valeurs réel
	inputDistance = enc->getDistance();
	inputOrientation = enc->getOrientation();

	// Application du filtre pour la génération du profil trapézoidale
	// et définition des consignes
	setPointDistance = filterDistance.filter(cp->getVitesseDistance(), cp->getConsigneDistance(), inputDistance, cp->isFreinEnable());
	setPointOrientation = filterOrientation.filter(cp->getVitesseOrientation(), cp->getConsigneOrientation(), inputOrientation, cp->isFreinEnable());

	// Calcul du filtres PID
	//pidDistance.Compute();
	//pidOrientation.Compute();

	// Envoi des consignes aux moteurs
	cp->setCmdDroit(outputDistance + outputOrientation);
	cp->setCmdGauche(outputDistance - outputOrientation);

#ifdef DEBUG_MODE
	/*Serial.print("\tIn. : D -> ");
	Serial.print(inputDistance);
	Serial.print(" ; O -> ");
	Serial.print(inputOrientation);*/
	Serial.print(" ; SetP. : D -> ");
	Serial.print(setPointDistance);
	Serial.print(" ; O -> ");
	Serial.print(setPointOrientation);
	/*Serial.print(" ; Out. : D -> ");
	Serial.print(outputDistance);
	Serial.print(" ; O -> ");
	Serial.print(outputOrientation);
	Serial.print(" ; Cons. : D -> ");
	Serial.print(cp->getConsigneDistance());
	Serial.print(" ; O -> ");
	Serial.print(cp->getConsigneOrientation());*/

	/*Serial.print("\tCMD Asserv : D -> ");
	Serial.print(cp->getCmdDroit());
	Serial.print(" ; G -> ");
	Serial.print(cp->getCmdGauche());*/
#endif
}

// -------------------------------------------------------------- //
// ---------------------- GETTERS / SETTERS --------------------- //
// -------------------------------------------------------------- //

void Asservissement::setSampleTimeMs(unsigned int sampleTime) {
	this->sampleTime = sampleTime;
	pidDistance.SetSampleTime(sampleTime);
	pidOrientation.SetSampleTime(sampleTime);
	filterDistance.setSampleTimeMs(sampleTime);
	filterOrientation.setSampleTimeMs(sampleTime);
}

unsigned int Asservissement::getSampleTimeMs() {
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
