/*
 * RobotConsigne.h
 *
 *  Created on: 16 avr. 2013
 *      Author: mythril
 */

#ifndef ROBOTCONSIGNE_H_
#define ROBOTCONSIGNE_H_

#include <Arduino.h>
#include "RobotPosition.h"
#include "ConsignePolaire.h"

#define CONSIGNE_XY 			1
#define CONSIGNE_DIST			2
#define CONSIGNE_ANGLE			4

#define CONSIGNE_LINE			8
#define CONSIGNE_CIRCLE			16

//  y (2000)
//  |
//  |
//  |
//  |
//  |
//  |---------------------------------- x (3000)
// 0,0
// Theta = 0 dans le sens de X

class RobotConsigne {
public:
	RobotConsigne();

	RobotPosition & getPosition();

	ConsignePolaire & getConsignePolaire();

	void enableFrein();
	void disableFrein();
	boolean getFrein();

	void setType(char type);
	char getType();
private:
	RobotPosition position;
	ConsignePolaire consignePolaire;

	char type;
};

#endif /* ROBOTCONSIGNE_H_ */
