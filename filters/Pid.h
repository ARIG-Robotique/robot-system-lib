/*
 * Pid.h
 *
 *  Created on: 3 mai 2013
 *      Author: mythril
 */

#ifndef PID_H_
#define PID_H_

class Pid {
public:
	Pid();

	void setTunings(double kp, double ki, double kd);
	void reset();
	double compute(double consigne, double mesure);


private:
	double kp;
	double ki;
	double kd;

	double errorSum;
	double lastError;
};

#endif /* PID_H_ */
