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

//  y (2000)
//  |
//  |
//  |
//  |
//  |
//  |---------------------------------- x (3000)
// 0,0
// Theta = 0 dans le sens de Y

class RobotConsigne {
public:
	RobotConsigne();

	RobotPosition getPosition();

	void setFrein(boolean frein);
	boolean getFrein();
private:
	RobotPosition position;
	boolean frein;
};

#endif /* ROBOTCONSIGNE_H_ */
