/*
 * LMD18200.cpp
 *
 *  Created on: 20 janv. 2013
 *      Author: mythril
 */

#include "LMD18200.h"

/*
 * Constructeurs.
 */
LMD18200::LMD18200() : AbstractMotors() {
}

/*
 * Envoi des commandes au moteur 1
 */
void LMD18200::moteur1(int val) {
	int cmd = check(val);
	if (cmd == prevM1) {
		return;
	}
	prevM1 = cmd;

	// TODO : Implementation de la commande
}

/*
 * Envoi des commandes au moteur 2
 */
void LMD18200::moteur2(int val) {
	int cmd = check(val);
	if (cmd == prevM2) {
		return;
	}
	prevM2 = cmd;

	// TODO : Implémentation de la commande
}

#ifdef DEBUG_MODE
/*
 * Cette méthode affiche la version de la carte sur la liaison serie en mode debug
 */
void LMD18200::printVersion() {
	// TODO : Externaliser la version
	Serial.println(" - LMD18200 DC Motors [OK] (V : 0.1)");
}
#endif
