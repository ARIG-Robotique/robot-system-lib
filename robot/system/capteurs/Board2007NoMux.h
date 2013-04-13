/*
 * Board2007NoMux.h
 *
 *  Created on: 13 avr. 2013
 *      Author: mythril
 *
 * Gestion des capteurs de la carte de 2007 en accès direct (sans les MUX)
 */

#ifndef BOARD2007NOMUX_H_
#define BOARD2007NOMUX_H_

#include <Arduino.h>

#define CAPTEUR_01	0
#define CAPTEUR_02	1
#define CAPTEUR_03	2
#define CAPTEUR_04	3
#define CAPTEUR_05	4
#define CAPTEUR_06	5
#define CAPTEUR_07	6
#define CAPTEUR_08	7
#define CAPTEUR_09	8
#define CAPTEUR_10	9
#define CAPTEUR_11	10
#define CAPTEUR_12	11
#define CAPTEUR_13	12
#define CAPTEUR_14	13
#define CAPTEUR_15	14
#define CAPTEUR_16	15
#define CAPTEUR_17	16
#define CAPTEUR_18	17
#define CAPTEUR_19	18
#define CAPTEUR_20	19
#define CAPTEUR_21	20
#define CAPTEUR_22	21
#define CAPTEUR_23	22
#define CAPTEUR_24	23

class Board2007NoMux {
public:
	Board2007NoMux();

	void setPinForCapteur(char capteurId, char pin);
	char readCapteurValue(char capteurId);

private:
#define	NB_CAPTEUR	24;

	char capteurPins[24] = {};

	boolean check(char capteurId);
};

#endif /* BOARD2007NOMUX_H_ */
