/*
 * AbstractMotors.h
 *
 *  Created on: 22 juin 2013
 *      Author: mythril
 */

#ifndef ABSTRACTMOTORS_H_
#define ABSTRACTMOTORS_H_

#include "../../../common.h"

class AbstractMotors {
public:
	AbstractMotors();

	void init();
	void assignMotors(int numMoteurGauche, int numMoteurDroit);
	void generateMouvement(int gauche, int droit);
	void moteurGauche(int cmd);
	void moteurDroit(int cmd);
	void stopAll();
	void stopGauche();
	void stopDroit();
	void stop1();
	void stop2();


	void moteur1(int cmd); // A définir dans les classes filles
	void moteur2(int cmd); // A définir dans les classes filles

#ifdef DEBUG_MODE
	void printVersion(); // A surcharger si besoin dans les classes filles
#endif

protected:
	int minVal;
	int maxVal;

	int prevM1;
	int prevM2;

	int check(int);

private:
	// Constantes pour la configuration des moteurs
	#define ASSIGN_UNDEF_MOTOR		0
	#define ASSIGN_MOTOR_1			1
	#define ASSIGN_MOTOR_2			2

	char numMoteurGauche, numMoteurDroit;

	bool alternate;
};

#endif /* ABSTRACTMOTORS_H_ */
