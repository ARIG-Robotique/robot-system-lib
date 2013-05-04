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
double QuadRamp::filter(double vitesse, double consigne, int frein) {
	// Calcul de la distance de décéleration en fonction des parametres
	distanceDecel = Conv.mmToPulse((vitesseCourante * vitesseCourante) / (2 * rampDec));
	if (vitesseCourante > vitesse || (abs(consigne) <= distanceDecel && frein == FREIN_ACTIF)) {
		vitesseCourante -= rampDec * sampleTime;
	} else if (vitesseCourante < vitesse && abs(consigne) > distanceDecel) {
		vitesseCourante += rampAcc * sampleTime;
	}

	// Controle pour interdire les valeurs négatives
	vitesseCourante = fmax(vitesseCourante, 0);

	// Calcul de la valeur théorique en fonction de la vitesse.
	double pulseForVitesse = Conv.mmToPulse(vitesseCourante) * sampleTime;

	// Consigne théorique en fonction de la vitesse
	double ecartTheorique = pulseForVitesse;
	if (consigne < 0) {
		ecartTheorique = -ecartTheorique;
	}

#ifdef DEBUG_MODE
	Serial.print(";FVit. ");Serial.print(vitesseCourante);
	Serial.print(";FDistD");Serial.print(distanceDecel);
	Serial.print(";FCons.");Serial.print(consigne);
	Serial.print(";FOut");Serial.print(ecartTheorique);
#endif

	return ecartTheorique;
}

/*
 * /!\ EXPERIMENTAL
 *
 * Application du filtre "logarithmique".
 * Cette méthode est appelé depuis la sub routine d'asservissement
 */
double QuadRamp::filterLog(double vitesse, double consigne, double mesure, int frein) {
	// Récupération de la version normal et ajout de l'écart précedent
	double ecartTheorique = filter(vitesse, consigne, frein) + ecartPrecedent;
	ecartPrecedent = ecartTheorique - mesure;

#ifdef DEBUG_MODE
	Serial.print(";FOutLog");Serial.print(ecartTheorique);
#endif

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

