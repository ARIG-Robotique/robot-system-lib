/*
 * Noeud.cpp

 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#include "Noeud.h"
#include <stdlib.h>
#include <Arduino.h>

Noeud::Noeud()
{
	//_Point = NULL;
	//_PointParent =NULL;
	_CoutG=-1;
	_CoutF=-1;
	_CoutH=-1;

}

Noeud::Noeud(Point p)
{
	_Point = p;
	//_PointParent = NULL;
	_CoutG=-1;
	_CoutF=-1;
	_CoutH=-1;

}

Noeud::Noeud(Point p, Point pParent)
{
	_Point = p;
	_PointParent = pParent;
	_CoutG=-1;
	_CoutF=-1;
	_CoutH=-1;
}

Point Noeud::getPoint()
{
	return _Point;
}

Point Noeud::getPointParent()
{
	return _PointParent;
}

void Noeud::setPoint(Point p)
{
	_Point = p;
}

void Noeud::setPointParent(Point pParent)
{
	_PointParent = pParent;
}

int Noeud::getCoutG()
{
	return _CoutG;
}

void Noeud::setCoutG(int coutG)
{
	_CoutG = coutG;
}

int Noeud::getCoutH()
{
	return _CoutH;
}

void Noeud::setCoutH( int coutH)
{
	_CoutH = coutH;
}

int Noeud::getCoutF()
{
	return _CoutF;
}

void Noeud::setCoutF( int coutF)
{
	_CoutF = coutF;
}

#ifdef DEBUG_ASTAR
String Noeud::toString(){


	String retour;

	/*retour = "Point X : " + _Point.getX();
	retour += "Y : " + _Point.getY();*/

	retour ="lolo";

	/*if(_PointParent != NULL){
		retour = retour + "PointParent X : " + _PointParent.getX() + "Y : " + _PointParent.getY();
	}
	else
	{
		retour = retour + "PointParent NULL";
	}*/
	return retour;

}
#endif
