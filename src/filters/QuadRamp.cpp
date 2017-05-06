/*
 * Quad.cpp
 *
 *  Created on: 7 janv. 2013
 *      Author: mythril
 */

#include "QuadRamp.h"

#include <Arduino.h>
#include "../utils/Convertion.h"
#include "../robot/vo/ConsignePolaire.h"

/*
 * Constructeur par défaut
 */
QuadRamp::QuadRamp() {
	this->sampleTime = 0.010;
	this->rampAcc = 100.0;
	this->rampDec = 100.0;

	QuadRamp::reset();
	QuadRamp::updateStepVitesse();
}

/*
 * Constructeur
 */
QuadRamp::QuadRamp(double sampleTime, double rampAcc, double rampDec) {
	this->sampleTime = sampleTime / 1000;
	this->rampAcc = rampAcc;
	this->rampDec = rampDec;

	QuadRamp::reset();
	QuadRamp::updateStepVitesse();
}

// --------------------------------------------------------- //
// --------------------- BUSINESS METHODS ------------------ //
// --------------------------------------------------------- //

/*
 * Réinitialisation des paramètres du filtre
 */
void QuadRamp::reset() {
	distanceDecel = 0;
	ecartPrecedent = 0;
	vitesseCourante = 0;
}

/*
 * Application du filtre.
 * Cette méthode est appelé depuis la sub routine d'asservissement
 */
double QuadRamp::filter(double vitesse, double consigne, boolean frein) {
	// Calcul de la distance de décéleration en fonction des parametres
	distanceDecel = Conv.mmToPulse((vitesseCourante * vitesseCourante) / (2 * rampDec));
	if (vitesseCourante > vitesse || (abs(consigne) <= distanceDecel && frein)) {
		vitesseCourante -= stepVitesseDecel;
	} else if (vitesseCourante < vitesse) {
		vitesseCourante += stepVitesseAccel;
	}

	// Valeur max (evite les oscilations en régime établie)
	vitesseCourante = fmin(vitesseCourante, vitesse);

	// Controle pour interdire les valeurs négatives
	vitesseCourante = fmax(vitesseCourante, 0);

	// Calcul de la valeur théorique en fonction de la vitesse.
	double pulseForVitesse = Conv.mmToPulse(vitesseCourante) * sampleTime;

	// Consigne théorique en fonction de la vitesse
	double ecartTheorique = pulseForVitesse;
	if (consigne < 0) {
		ecartTheorique = -ecartTheorique;
	}

	return ecartTheorique;
}

/*
 * /!\ EXPERIMENTAL
 *
 * Application du filtre "logarithmique".
 * Cette méthode est appelé depuis la sub routine d'asservissement
 *
 * FIXME : ça merde lors de la phase de décéleration.
 */
double QuadRamp::filterLog(double vitesse, double consigne, double mesure, boolean frein) {
	// Récupération de la version normal et ajout de l'écart précedent
	double ecartTheorique = filter(vitesse, consigne, frein) + ecartPrecedent;
	ecartPrecedent = ecartTheorique - mesure;

#ifdef DEBUG_MODE
	//Serial.print(";FOutLog");Serial.print(ecartTheorique);
#endif

	return ecartTheorique;
}

// --------------------------------------------------------- //
// -------------------- GETTERS / SETTERS ------------------ //
// --------------------------------------------------------- //

void QuadRamp::setSampleTimeMs(double value) {
	sampleTime = value / 1000;
	updateStepVitesse();
}

void QuadRamp::setRampAcc(double value) {
	rampAcc = value;
	updateStepVitesse();
}

void QuadRamp::setRampDec(double value) {
	rampDec = value;
	updateStepVitesse();
}

void QuadRamp::updateStepVitesse() {
	stepVitesseAccel = rampAcc * sampleTime;
	stepVitesseDecel = rampDec * sampleTime;
}
