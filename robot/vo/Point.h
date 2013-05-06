/*
 * Point.h
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#ifndef POINT_H_
#define POINT_H_

class Point
{
	public :
		Point();
		Point(int x, int y);
		Point(Point *p);

		int getX();
		int getY();
		void setX(int x);
		void setY (int y);
		bool equal(Point p);

	private :
		int _X;
		int _Y;
};


#endif /* POINT_H_ */
