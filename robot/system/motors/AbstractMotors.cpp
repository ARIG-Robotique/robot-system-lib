/*
 * AbstractMotors.cpp
 *
 *  Created on: 22 juin 2013
 *      Author: mythril
 */

#include "AbstractMotors.h"

#include <Arduino.h>

AbstractMotors::AbstractMotors() {
	assignMotors(ASSIGN_UNDEF_MOTOR, ASSIGN_UNDEF_MOTOR);
	alternate = false;
}


/* *********************************** */
/* ********* PUBLIC METHODS ********** */
/* *********************************** */

/*
 * Méthode d'initialisation pour la commande moteurs
 */
void AbstractMotors::init() {
	// Cette méthode est a surcharger au besoin
	Serial.println(" * Rien de particulier a initialiser");
}

/*
 * Méthode pour assigner le numéro du moteur pour la commande gauche / droite
 */
void AbstractMotors::assignMotors(int numMoteurGauche, int numMoteurDroit) {
	this->numMoteurGauche = numMoteurGauche;
	this->numMoteurDroit = numMoteurDroit;
}

/*
 * Méthode de génération groupé de la commande droite / gauche
 */
void AbstractMotors::generateMouvement(int gauche, int droit) {
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
 * Méthode de commande du moteur gauche (doit être assigné)
 */
void AbstractMotors::moteurGauche(int cmd) {
	if (numMoteurGauche == ASSIGN_MOTOR_1) {
		moteur1(cmd);
	} else if (numMoteurGauche == ASSIGN_MOTOR_2) {
		moteur2(cmd);
	}
}

/*
 *  Méthode de commande du moteur droit (doit être assigné)
 */
void AbstractMotors::moteurDroit(int cmd) {
	if (numMoteurDroit == ASSIGN_MOTOR_1) {
		moteur1(cmd);
	} else if (numMoteurDroit == ASSIGN_MOTOR_2) {
		moteur2(cmd);
	}
}

/*
 * Méthode pour commander l'arret des moteurs configuré
 */
void AbstractMotors::stopAll() {
	stop1();
	stop2();
}

/*
 * Méthode d'arrêt du moteur gauche (doit être assigné)
 */
void AbstractMotors::stopGauche() {
	if (numMoteurGauche == ASSIGN_MOTOR_1) {
		stop1();
	} else if (numMoteurGauche == ASSIGN_MOTOR_2) {
		stop2();
	}
}

/*
 * Méthode d'arret du moteur droit (doit être assigné)
 */
void AbstractMotors::stopDroit() {
	if (numMoteurDroit == ASSIGN_MOTOR_1) {
		stop1();
	} else if (numMoteurDroit == ASSIGN_MOTOR_2) {
		stop2();
	}
}

/*
 * Méthode d'arrêt du moteur 1
 */
void AbstractMotors::stop1() {
	moteur1(0);
}

/*
 * Méthode d'arrêt du moteur 2
 */
void AbstractMotors::stop2() {
	moteur2(0);
}

/*
 * Méthode de contrôle du bornage des commandes moteurs
 */
int AbstractMotors::check(int val) {
	if (val < minVal) {
		val = minVal;
	}
	if (val > maxVal) {
		val = maxVal;
	}

	return val;
}

#ifdef DEBUG_MODE
/*
 * Cette méthode affiche la version de la carte sur la liaison serie en mode debug
 */
void AbstractMotors::printVersion() {
	Serial.println(" - AbstractMotor [OK] (V : UNKOWN)");
}
#endif
