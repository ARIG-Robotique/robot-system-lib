/*
 * LMD18200.h
 *
 *  Created on: 20 janv. 2013
 *      Author: mythril
 */

#ifndef LMD18200_H_
#define LMD18200_H_

#include "AbstractMotors.h"

// TODO : Implémenter la gestion des moteurs sur carte LMD18200

class LMD18200: public AbstractMotors {
public:
	LMD18200();
	virtual ~LMD18200();

	// Implémentation méthode virtuel //
	virtual void moteur1(int cmd);
	virtual void moteur2(int cmd);

#ifdef DEBUG_MODE
	virtual void printVersion();
#endif
};

#endif /* LMD18200_H_ */
