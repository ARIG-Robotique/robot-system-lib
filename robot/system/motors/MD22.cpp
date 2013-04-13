/*
 * MD22.cpp
 *
 *  Created on: 26 d�c. 2012
 *      Author: mythril
 */

#include "MD22.h"

#include <Arduino.h>
#include <Wire.h>

/*
 * Constucteur
 */
MD22::MD22() {
	alternate = false;
	modeValue = DEFAULT_MODE_VALUE;
	accelValue = DEFAULT_ACCEL_VALUE;
}

MD22::MD22(int mode, int accel) {
	alternate = false;
	modeValue = mode;
	accelValue = accel;
}

/*
 * Envoi d'une consigne sur le moteur Gauche
 */
void MD22::moteurGauche(int val) {
	Wire.beginTransmission(MD22_ADD_BOARD);
	Wire.write(LEFT_MOTOR_REGISTER);
	Wire.write(check(val));
	Wire.endTransmission();
}

void MD22::moteur1(int val) {
	moteurGauche(val);
}

/*
 * Envoi d'une consigne sur le moteur Droit
 */
void MD22::moteurDroit(int val) {
	Wire.beginTransmission(MD22_ADD_BOARD);
	Wire.write(RIGHT_MOTOR_REGISTER);
	Wire.write(check(val));
	Wire.endTransmission();
}

void MD22::moteur2(int val) {
	moteurDroit(val);
}

/*
 * Cette fonction permet de controler les bornes min et max en fonction du mode.
 */
int MD22::check(int val) {
	if (val < minVal) {
		val = minVal;
	}
	if (val > maxVal) {
		val = maxVal;
	}

	return val;
}

/*
 * Generation des mouvements pour le robot.
 * La commande de chacun des moteurs est altern� a chaque commande.
 * Cela est fait pour ne pas p�nalis� un cot� vis a vis d'un autre.
 * Normalement le PID devrais g�rer �a, mais bon ceinture et bretelle.
 */
void MD22::generateMouvement(int gauche, int droit) {
	alternate = !alternate;
	if (alternate) {
		moteurGauche(gauche);
		moteurDroit(droit);
	} else {
		moteurDroit(droit);
		moteurGauche(gauche);
	}
}

/*
 * Stop les moteurs en fonction de la valeur de l'acceleration
 */
void MD22::stopAll() {
	stopDroit();
	stopGauche();
}

/*
 * Stop le moteur droit.
 */
void MD22::stopDroit() {
	moteurDroit(stopVal);
}

void MD22::stop2() {
	stopDroit();
}

/*
 * Stop le moteur gauche
 */
void MD22::stopGauche() {
	moteurGauche(stopVal);
}

void MD22::stop1() {
	stopGauche();
}

/*
 * Initialisation de la carte MD22.
 * La configuration du mode
 */
void MD22::init() {
	setMode(modeValue);
	delayMicroseconds(100);
	setAccel(accelValue);

	stopAll();
}

/*
 * Configuration de la valeur d'acc�leration des moteurs.
 * L'acc�leration fonctionne comme suit :
 *
 * If you require a controlled acceleration period for the attached motors to reach there ultimate speed,
 * the MD22 has a register to provide this. It works by inputting a value into the acceleration register
 * which acts as a delay in the power stepping. The amount of steps is the difference between the current
 * speed of the motors and the new speed (from speed 1 and 2 registers). So if the motors were traveling
 * at full speed in the forward direction (255) and were instructed to move at full speed in reverse (0),
 * there would be 255 steps.
 *
 * The acceleration register contains the rate at which the motor board moves through the steps. At 0 (default)
 * the board changes the power (accelerates) at its fastest rate, each step taking 64us. When the acceleration
 * register is loaded with the Slowest setting of 255, the board will change the power output every 16.4ms.
 *
 * So to calculate the time (in seconds) for the acceleration to complete : time = accel reg value * 64us * steps.
 * For example :
 *
 * ----------------------------------------------------------------------------------
 * | Accel reg 	| Time/step	| Current speed	| New speed	| Steps	| Acceleration time	|
 * ----------------------------------------------------------------------------------
 * | 0			| 0			| 0				| 255		| 255	| 0					|
 * ----------------------------------------------------------------------------------
 * | 20			| 1.28ms	| 127			| 255		| 128	| 164ms				|
 * ----------------------------------------------------------------------------------
 * | 50			| 3.2ms		| 80			| 0			| 80	| 256ms				|
 * ----------------------------------------------------------------------------------
 * | 100		| 6.4ms		| 45			| 7			| 38	| 243ms				|
 * ----------------------------------------------------------------------------------
 * | 150		| 9.6ms		| 255			| 5			| 250	| 2.4s				|
 * ----------------------------------------------------------------------------------
 * | 200		| 12.8ms	| 127			| 0			| 127	| 1.63s				|
 * ----------------------------------------------------------------------------------
 * | 255		| 16.32ms	| 65			| 150		| 85	| 1.39s				|
 * ----------------------------------------------------------------------------------
 */
void MD22::setAccel(char value) {
	if (value < 0)
		value = 0;
	if (value > 255)
		value = 255;

	accelValue = value;

	// Set accelleration
	Wire.beginTransmission(MD22_ADD_BOARD);
	Wire.write(ACCEL_REGISTER);
	Wire.write(value);
	Wire.endTransmission();
}

/*
 * Configuration du mode de la carte MD22.
 * Les modes 0 et 1 sont g�r� uniquement.
 */
void MD22::setMode(char value) {
	modeValue = value;
	switch (modeValue) {
		case MODE_0:
			minVal = MIN_VAL_MODE_0;
			maxVal = MAX_VAL_MODE_0;
			stopVal = STOP_VAL_MODE_0;
			break;

		case MODE_1 :
		default:
			minVal = MIN_VAL_MODE_1;
			maxVal = MAX_VAL_MODE_1;
			stopVal = STOP_VAL_MODE_1;
			break;
	}

	// Set mode
	Wire.beginTransmission(MD22_ADD_BOARD);
	Wire.write(MODE_REGISTER);
	Wire.write(modeValue);
	Wire.endTransmission();
}

/*
 * Cette m�thode affiche la version de la carte sur la liaison serie en mode debug
 */
void MD22::printVersion() {
	Wire.beginTransmission(MD22_ADD_BOARD);
	Wire.write(MD22_VERSION_REGISTER);
	Wire.endTransmission();

	Wire.requestFrom(MD22_ADD_BOARD, 1);
	while(Wire.available() < 1);
	int software = Wire.read();

	Serial.print(" - MD22 [OK] (V : ");
	Serial.print(software);
	Serial.println(")");
}

