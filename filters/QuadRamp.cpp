/*
 * Quad.cpp
 *
 *  Created on: 7 janv. 2013
 *      Author: mythril
 */

#include "QuadRamp.h"

#include <Arduino.h>
#include "../robot/utils/Convertion.h"

/*
 * Constructeur
 */
QuadRamp::QuadRamp() {
	this->sampleTime = 0;
	this->rampAcc = 0;
	this->rampDec = 0;

	this->distanceDecel = 0;
	this->ecartPrecedent = 0;
	this->vitesseCourante = 0;
}

/*
 * Constructeur
 */
QuadRamp::QuadRamp(int sampleTime, double rampAcc, double rampDec) {
	this->sampleTime = sampleTime;
	this->rampAcc = rampAcc;
	this->rampDec = rampDec;

	this->distanceDecel = 0;
	this->ecartPrecedent = 0;
	this->vitesseCourante = 0;
}

// --------------------------------------------------------- //
// --------------------- BUSINESS METHODS ------------------ //
// --------------------------------------------------------- //

/*
 * Application du filtre.
 * Cette mŽthode est appelŽ depuis la sub routine d'asservissement
 */
double QuadRamp::filter(double vitesse, double consigne, double mesure, bool frein) {
	// Calcul de la distance de dŽcŽleration en fonction des parametres
	distanceDecel = Conv.mmToPulse((this->vitesseCourante * this->vitesseCourante) / (2 * this->rampDec));
	if (vitesseCourante > vitesse	|| (abs(consigne) <= distanceDecel && frein)) {
		vitesseCourante -= rampDec * sampleTime;
	} else if (vitesseCourante < vitesse) {
		vitesseCourante += rampAcc * sampleTime;
	}

	// Controle pour interdire les valeurs nŽgatives
	vitesseCourante = fmax(vitesseCourante, 0);

	// Calcul de la valeur thŽorique en fonction de la vitesse.
	double pulseForVitesse = Conv.mmToPulse(vitesseCourante) * sampleTime;

	// Consigne thŽorique en de la vitesse et du temps ŽcoulŽ
	double ecartTheorique = pulseForVitesse + abs(ecartPrecedent);
	if (consigne < 0) {
		ecartTheorique = -ecartTheorique;
	}
	ecartPrecedent = ecartTheorique - mesure;

	return ecartTheorique;
}

// --------------------------------------------------------- //
// -------------------- GETTERS / SETTERS ------------------ //
// --------------------------------------------------------- //

void QuadRamp::setSampleTime(int value) {
	this->sampleTime = value;
}

void QuadRamp::setRampAcc(double value) {
	this->rampAcc = value;
}

void QuadRamp::setRampDec(double value) {
	this->rampDec = value;
}

