/*
 * MD22.h
 *
 *  Created on: 26 déc. 2012
 *      Author: mythril
 */

#ifndef MD22_H_
#define MD22_H_

#include <Arduino.h>
#include "../../utils/I2CUtils.h"
#include "../../../common.h"

class MD22 {

public:
	MD22();
	MD22(byte mode, byte accel);

	void init();
	void generateMouvement(int gauche, int droit);
	void moteurGauche(int);
	void moteurDroit(int);
	void moteur1(int);
	void moteur2(int);
	void stopAll();
	void stopGauche();
	void stopDroit();
	void stop1();
	void stop2();
	void setMode(byte value);
	void setAccel(byte value);

#ifdef DEBUG_MODE
	void printVersion();
#endif

private:
	#define MD22_ADD_BOARD			0x58

	#define MODE_REGISTER			0x00
	#define ACCEL_REGISTER			0x03
	#define LEFT_MOTOR_REGISTER		0x02
	#define RIGHT_MOTOR_REGISTER	0x01
	#define MD22_VERSION_REGISTER	0x07

	#define MODE_0					0 // 0 (Reverse) - 128 (Stop) - 255 (Forward)
	#define MODE_1					1 // -128 (Reverse) - 0 (Stop) - 127 (Forward)

	#define DEFAULT_MODE_VALUE		MODE_1
	#define DEFAULT_ACCEL_VALUE		0 // Pas d'acceleration

	#define MIN_VAL_MODE_0			0
	#define STOP_VAL_MODE_0			128
	#define MAX_VAL_MODE_0			255

	#define MIN_VAL_MODE_1			-128
	#define STOP_VAL_MODE_1			0
	#define MAX_VAL_MODE_1			127

	byte retCode;
	bool alternate;
	char modeValue;
	char accelValue;
	int minVal;
	int maxVal;
	int stopVal;
	int prevGauche;
	int prevDroit;

	int check(int);
	void setMode(byte value, boolean transmit);
	void setAccel(byte value, boolean transmit);
	void init(boolean transmit);
};

#endif /* MD22_H_ */
