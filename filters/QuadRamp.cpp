/*
 * Quad.cpp
 *
 *  Created on: 7 janv. 2013
 *      Author: mythril
 */

#include "QuadRamp.h"

#include <Arduino.h>
#include "../robot/utils/Convertion.h"
#include "../robot/vo/ConsignePolaire.h"

/*
 * Constructeur
 */
QuadRamp::QuadRamp() {
	sampleTime = 0;
	rampAcc = 0;
	rampDec = 0;

	distanceDecel = 0;
	ecartPrecedent = 0;
	vitesseCourante = 0;
}

/*
 * Constructeur
 */
QuadRamp::QuadRamp(double sampleTime, double rampAcc, double rampDec) {
	this->sampleTime = sampleTime / 1000;
	this->rampAcc = rampAcc;
	this->rampDec = rampDec;

	distanceDecel = 0;
	ecartPrecedent = 0;
	vitesseCourante = 0;
}

// --------------------------------------------------------- //
// --------------------- BUSINESS METHODS ------------------ //
// --------------------------------------------------------- //

/*
 * Application du filtre.
 * Cette méthode est appelé depuis la sub routine d'asservissement
 */
double QuadRamp::filter(double vitesse, double consigne, double mesure, byte frein) {
	// Calcul de la distance de décéleration en fonction des parametres
	distanceDecel = Conv.mmToPulse((vitesseCourante * vitesseCourante) / (2 * rampDec));
	if (vitesseCourante > vitesse	|| (abs(consigne) <= distanceDecel && frein == FREIN_ACTIF)) {
		vitesseCourante -= rampDec * sampleTime;
	} else if (vitesseCourante < vitesse && consigne != 0) {
		vitesseCourante += rampAcc * sampleTime;
	}

	// Controle pour interdire les valeurs négatives
	vitesseCourante = fmax(vitesseCourante, 0);

	// Calcul de la valeur théorique en fonction de la vitesse.
	double pulseForVitesse = Conv.mmToPulse(vitesseCourante) * sampleTime;

	// Consigne théorique en de la vitesse et du temps écoulé
	double ecartTheorique = pulseForVitesse + abs(ecartPrecedent);
	if (consigne < 0) {
		ecartTheorique = -ecartTheorique;
	}
	ecartPrecedent = ecartTheorique - mesure;

/*#ifdef DEBUG_MODE
	Serial.print(";F");
	Serial.print(frein);
	Serial.print(";V");
	Serial.print(vitesseCourante);
	Serial.print(";DD");
	Serial.print(distanceDecel);
	Serial.print(";M");
	Serial.print(mesure);
	Serial.print(";C");
	Serial.print(consigne);
	Serial.print(";E");
	Serial.print(ecartTheorique);
	Serial.print("\t");
#endif*/

	return ecartTheorique;
}

// --------------------------------------------------------- //
// -------------------- GETTERS / SETTERS ------------------ //
// --------------------------------------------------------- //

void QuadRamp::setSampleTimeMs(double value) {
	sampleTime = value / 1000;
}

void QuadRamp::setRampAcc(double value) {
	rampAcc = value;
}

void QuadRamp::setRampDec(double value) {
	rampDec = value;
}

