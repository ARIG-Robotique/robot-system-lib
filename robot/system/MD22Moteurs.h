/*
 * MD22Moteurs.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef MD22MOTEURS_H_
#define MD22MOTEURS_H_

class MD22Moteurs {
public:
	MD22Moteurs();
	virtual ~MD22Moteurs();

	void generateMouvement(int gauche, int droit);
	void init();
	void printVersion();
private:

	#define ADD_BOARD			0xB4

	#define MODE_REGISTER		0x00
	#define MODE_VALUE			1 // -128 (Reverse) - 0 (Stop) - 127 (Forward)

	#define LEFT_MOTOR			1
	#define RIGHT_MOTOR			2

	#define VERSION_REGISTER	7

	#define ACCEL_REGISTER		3
	#define ACCEL_VALUE			20

	#define MIN_VAL 			-128
	#define MAX_VAL				127

	bool alternate;

	void moteurGauche(int);
	void moteurDroit(int);

	int check(int);
};

#endif /* MD22MOTEURS_H_ */
