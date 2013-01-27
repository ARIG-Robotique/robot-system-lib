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
	RobotPosition();

	void updatePosition(double x, double y, int angle);

	void setX(double x);
	double getX();

	void setY(double y);
	double getY();

	void setAngle(int angle);
	int getAngle();

private:
	double x, y;
	int angle;
};

#endif /* ROBOTPOSITION_H_ */
