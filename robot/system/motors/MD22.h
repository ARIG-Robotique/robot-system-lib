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
	MD22Moteurs(int mode, int accel);

	void generateMouvement(int gauche, int droit);
	void stop();
	void setMode(char value);
	void setAccel(char value);
	void init();
	void printVersion();

private:
	#define ADD_BOARD				0xB4

	#define MODE_REGISTER			0
	#define ACCEL_REGISTER			3
	#define LEFT_MOTOR_REGISTER		1
	#define RIGHT_MOTOR_REGISTER	2
	#define VERSION_REGISTER		7

	#define MODE_0					0 // 0 (Reverse) - 128 (Stop) - 255 (Forward)
	#define MODE_1					1 // -128 (Reverse) - 0 (Stop) - 127 (Forward)

	#define DEFAULT_MODE_VALUE		MODE_1
	#define DEFAULT_ACCEL_VALUE		20

	#define MIN_VAL_MODE_0			0
	#define STOP_VAL_MODE_0			128
	#define MAX_VAL_MODE_0			255

	#define MIN_VAL_MODE_1			-128
	#define STOP_VAL_MODE_1			0
	#define MAX_VAL_MODE_1			127

	bool alternate;
	char modeValue;
	char accelValue;
	int minVal;
	int maxVal;
	int stopVal;

	void moteurGauche(int);
	void moteurDroit(int);

	int check(int);
};

#endif /* MD22MOTEURS_H_ */
