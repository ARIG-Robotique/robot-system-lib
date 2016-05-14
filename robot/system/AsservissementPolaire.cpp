/*
 * Asservissement.cpp
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#include "AsservissementPolaire.h"
#include "../../utils/Convertion.h"

/*
 * Constructeur par défaut
 */
AsservissementPolaire::AsservissementPolaire() {
	setup();
}

/*
 * Constructeur
 */
AsservissementPolaire::AsservissementPolaire(byte sampleTime) {
	setup(sampleTime);
}

// -------------------------------------------------------------- //
// ----------------------- BUSINESS METHODS --------------------- //
// -------------------------------------------------------------- //

/*
 * Cette méthode initialise l'asservissement.
 * Les valeurs peuvent être modifié par les accesseurs.
 */
void AsservissementPolaire::setup(byte sampleTime) {
	minFenetreDistance = Conv.mmToPulse(50);
	minFenetreOrientation = Conv.degToPulse(10);

	// Variable
	this->sampleTime = sampleTime;
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
void AsservissementPolaire::process(AbstractEncodeurs * enc, ConsignePolaire & cp) {
	// Récupération des valeurs réel
	inputDistance = enc->getDistance();
	inputOrientation = enc->getOrientation();

	// Application du filtre pour la génération du profil trapézoidale et définition des consignes
	setPointDistance = filterDistance.filter(cp.getVitesseDistance(), cp.getConsigneDistance(), cp.getFrein());
	setPointOrientation = filterOrientation.filter(cp.getVitesseOrientation(), cp.getConsigneOrientation(), true);

	// Calcul du filtres PID
	outputDistance = pidDistance.compute(setPointDistance, inputDistance);
	outputOrientation = pidOrientation.compute(setPointOrientation, inputOrientation);

	// Envoi des consignes aux moteurs
	cp.setCmdDroit((int) (outputDistance + outputOrientation));
	cp.setCmdGauche((int) (outputDistance - outputOrientation));
}

void AsservissementPolaire::reset() {
	reset(false);
}

/*
 * Méthode pour effectuer un reset des PID et des filtres QuadRamp
 */
void AsservissementPolaire::reset(boolean resetFilter){
	pidDistance.reset();
	pidOrientation.reset();

	if (resetFilter) {
		filterDistance.reset();
		filterOrientation.reset();
	}
}

/*
 * Méthode permettant de récuperer la zone pour la fenetre en distance
 */
double AsservissementPolaire::getFenetreApprocheDistance() {
	// Application du théorème de Shannon
	// En gros l'idée est que la fenêtre varie en fonction de la vitesse afin qu'a pleine bourre on la dépasse pas
	// et que l'on se mette a faire des tours sur soit même
	return fmax(minFenetreDistance, 3 * setPointDistance);
}

/*
 * Méthode permettant de récuperer la zone pour la fenetre en distance
 */
double AsservissementPolaire::getFenetreApprocheOrientation() {
	// Application du théorème de Shannon
	// En gros l'idée est que la fenêtre varie en fonction de la vitesse afin qu'a pleine bourre on la dépasse pas
	// et que l'on se mette a faire des tours sur soit même
	return fmax(minFenetreOrientation, 3 * setPointOrientation);
}

// -------------------------------------------------------------- //
// ---------------------- GETTERS / SETTERS --------------------- //
// -------------------------------------------------------------- //

/*
 * Définition du temps en ms pour l'asservissement.
 * Cela permet de déterminer le pas de génération des profils de vitesses
 */
void AsservissementPolaire::setSampleTimeMs(byte sampleTime) {
	this->sampleTime = sampleTime;
	filterDistance.setSampleTimeMs(sampleTime);
	filterOrientation.setSampleTimeMs(sampleTime);
}

/*
 * Accesseur pour le temps d'asservissement
 */
byte AsservissementPolaire::getSampleTimeMs() {
	return this->sampleTime;
}

/*
 * Configuration du PID de distance
 */
void AsservissementPolaire::setPIDDistance(double kp, double ki, double kd) {
	pidDistance.setTunings(kp, ki, kd);
}

/*
 * Configuration du PID d'orientation
 */
void AsservissementPolaire::setPIDOrientation(double kp, double ki, double kd) {
	pidOrientation.setTunings(kp, ki, kd);
}

/*
 * Configuration des rampes d'acceleration
 */
void AsservissementPolaire::setRampAcc(double rampDistance, double rampOrientation) {
	filterDistance.setRampAcc(rampDistance);
	filterOrientation.setRampAcc(rampOrientation);
}

/*
 * Configuration des rampes de décéleration
 */
void AsservissementPolaire::setRampDec(double rampDistance, double rampOrientation) {
	filterDistance.setRampDec(rampDistance);
	filterOrientation.setRampDec(rampOrientation);
}
