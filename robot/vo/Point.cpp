/*
 * Point.cpp
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */


/*Declaration des fonctions de la classe Point*/

#include "Point.h"

Point::Point()
{
	_X=-1;
	_Y=-1;
}

Point::Point(int x, int y)
{
	_X = x;
	_Y = y;
}

Point::Point(Point *p)
{
	_X = p->getX();
	_Y = p->getY();
}

int Point::getX()
{
	return _X;
}

int Point::getY()
{
	return _Y;
}


void Point::setX(int x)
{
	_X =x;
}

void Point::setY(int y)
{
	_Y=y;
}


bool Point::equal(Point p)
{

	if(_X == p.getX() && _Y == p.getY())
	{
		return true;
	}
	else
	{
		return false;
	}

}



