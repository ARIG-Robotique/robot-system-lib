/*
 * RobotPosition.h
 *
 *  Created on: 22 déc. 2012
 *      Author: mythril
 */

#ifndef ROBOTPOSITION_H_
#define ROBOTPOSITION_H_

class RobotPosition {
public:
	RobotPosition(double X, double Y, int A);
	virtual ~RobotPosition();



private:
	double x, y, angle;
};

#endif /* ROBOTPOSITION_H_ */
