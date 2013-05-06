/*
 * Noeud.h
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#ifndef NOEUD_H_
#define NOEUD_H_

#include "Point.h"
#include <Arduino.h>

class Noeud
{
	public :
		Noeud();
		Noeud(Point p);
		Noeud(Point p,Point pParent);
		Point getPoint();
		Point getPointParent();
		void setPoint(Point p);
		void setPointParent(Point pParent);
		int getCoutG();
		void setCoutG(int coutG);
		int getCoutH();
		void setCoutH(int CoutH);
		int getCoutF();
		void setCoutF(int CoutF);


#ifdef DEBUG_ASTAR
		String toString();
#endif
	private :
		Point _Point;
		Point _PointParent;
		float _CoutG;
		float _CoutH;
		float _CoutF;
};


#endif /* NOEUD_H_ */
