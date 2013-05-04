/*
 * Asservissement.cpp
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#include "Asservissement.h"

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
Asservissement::Asservissement(byte sampleTime) {
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
	pidDistance = Pid();
	pidOrientation = Pid();

	// Configuration du filtre pour le profil trapézoïdale
	filterDistance = QuadRamp(sampleTime, 100, 100);
	filterOrientation = QuadRamp(sampleTime, 100, 100);
}

/*
 * Méthode de processing de l'asservissement polaire.
 */
void Asservissement::process(Encodeurs & enc, ConsignePolaire & cp) {
	// Récupération des valeurs réel
	inputDistance = enc.getDistance();
	inputOrientation = enc.getOrientation();

	// Application du filtre pour la génération du profil trapézoidale
	// et définition des consignes
	setPointDistance = filterDistance.filter(cp.getVitesseDistance(), cp.getConsigneDistance(), cp.getFrein());
	setPointOrientation = filterOrientation.filter(cp.getVitesseOrientation(), cp.getConsigneOrientation(), cp.getFrein());

	// Calcul du filtres PID
	outputDistance = pidDistance.compute(setPointDistance, inputDistance);
	outputOrientation = pidOrientation.compute(setPointOrientation, inputOrientation);

	// Envoi des consignes aux moteurs
	cp.setCmdDroit((int) (outputDistance + outputOrientation));
	cp.setCmdGauche((int) (outputDistance - outputOrientation));

#ifdef DEBUG_MODE
	/*Serial.print(";Cd ");
	Serial.print(cp.getConsigneDistance());
	Serial.print(";Co ");
	Serial.print(cp.getConsigneOrientation());

	Serial.print(";INd ");
	Serial.print(inputDistance);
	Serial.print(";SPd ");
	Serial.print(setPointDistance);

	Serial.print(";INo ");
	Serial.print(inputOrientation);
	Serial.print(";SPo ");
	Serial.print(setPointOrientation);

	Serial.print(";CmdD ");
	Serial.print(cp.getCmdDroit(), DEC);
	Serial.print(";CmdG ");
	Serial.print(cp.getCmdGauche(), DEC);
#endif
}

// -------------------------------------------------------------- //
// ---------------------- GETTERS / SETTERS --------------------- //
// -------------------------------------------------------------- //

void Asservissement::setSampleTimeMs(byte sampleTime) {
	this->sampleTime = sampleTime;
	filterDistance.setSampleTimeMs(sampleTime);
	filterOrientation.setSampleTimeMs(sampleTime);
}

byte Asservissement::getSampleTimeMs() {
	return this->sampleTime;
}

void Asservissement::setPIDDistance(double kp, double ki, double kd) {
	pidDistance.setTunings(kp, ki, kd);
}

void Asservissement::setPIDOrientation(double kp, double ki, double kd) {
	pidOrientation.setTunings(kp, ki, kd);
}

void Asservissement::setRampAcc(double rampDistance, double rampOrientation) {
	filterDistance.setRampAcc(rampDistance);
	filterOrientation.setRampDec(rampOrientation);
}

void Asservissement::setRampDec(double rampDistance, double rampOrientation) {
	filterDistance.setRampDec(rampDistance);
	filterOrientation.setRampDec(rampOrientation);
}
