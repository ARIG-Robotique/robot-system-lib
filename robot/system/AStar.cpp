/*
 * 		AStar.cpp
 *
 *  	Created on: 01 janv 2013
 *      	Author: Heiginko
 */

#include "WProgram.h"
#include "AStar.h"

/*Declaration des fonctions de la classe Point*/

Point::Point()
{
}

Point::Point(int x, int y)
{
	_X = x;
	_Y = y;
}

Point::Point(Point &p)
{
	_X = p.getX();
	_Y = p.getY();
}

int Point::getX()
{
	return _X
}

int Point::getY()
{
	return _Y
}

void Point::setX(int x)
{
	_X =x
}

void Point::setY(int y)
{
	_Y=y
}

/*Declaration des fonctions de la classe Noeud*/

Noeud::Noeud()
{
	_Point = NULL;
	_PointParent = NULL;
	_CoutG=-1;
	_CoutF=-1;
	_CoutH=-1;

}

Noeud::Noeud(Point p)
{
	_Point = p;
	_PointParent = NULL;
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

void Noeud::setCoutG( int coutG)
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

/*Declaration des fonctions de la classe listeObjects*/

ListeObjects::ListeObjects(){
	
	_PremierObject = NULL;
	_DernierObject = NULL;
	_CourantObject = NULL;
	_NbObjects = 0;
	_IndexCourant = -1	
	
}

boolean ListeObjects::isFinListe(){
	if(_IndexCourant>=NbObjects)
	{
		return true;
	}else{
		return false;
	}
}

boolean ListeObjects::isDebutListe(){
	if(_IndexCourant<=0)
	{
		return true;
	}else{
		return false;
	}
}

void ListeObjects::suivant()
{
	if(FinListe() == False && _CourantObject != NULL )
	{
		_CourantObject = _CourantObject->getObjectSuivant;
		_IndexCourant++;
	}	
}

void ListeObjects::precedent()
{
	if(DebutListe() ==false && _CourantObject != NULL)
	{
		_CourantObject = _CourantObject->getObjectPrecedent;
		_IndexCourant--;
	}
}

ObjectListe * ListeObjects::recupererObject()
{
	if(_CourantObject != NULL)
	{
		return _CourantObject;
	}
}

boolean ListeObjects::AjouterNoeud(Noeud n)
{
	ObjectListe * new_Object = malloc(size *new_Object);
	if(new_Object !=NULL)
	{
		new_Object->setNoeud(n);
		new_Object->setIndex(_NbObjects);
		_CourantObject = new_Object;
		_IndexCourant = _NbOjects;
		_NbObjects++;
		
		if(_PremierObject==NULL)
		{
			new_Object->setObjectSuivant(NULL);
			new_Object->setObjectPrecedent(NULL);
			_PremierObject = new_Object;
			_DernierObject = new_Object;
		}else{
			new_Object->setObjectPrecedent(_DernierObject);
			new_Object->setObjectSuivant(NULL);
			_DernierObject = new_Object;
		}
		return true;
	}else{
		return false;
	}
}



boolean ListeObjects:SupprimerNoeud(Noeud n)
{
	
}





