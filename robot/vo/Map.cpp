/*
 * Map.cpp
 *
 *  Created on: 1 mai 2013
 *      Author: daoh
 */

#include "Map.h"


Map::Map(int tailleX, int tailleY)
{

	int i;

	_TailleX = tailleX;
	_TailleY = tailleY;

	/*Allocation du tableau*/

	_Tableau = malloc(_TailleX * sizeof(*_Tableau));
	for(i = 0;_TailleX;i++ )
	{
		_Tableau[i] = malloc(_TailleY * sizeof(*(_Tableau[i])));
	}

}

int Map::getTailleX()
{
	return _TailleX;
}

int Map::getTailleY()
{
	return _TailleY;
}

bool Map::isFranchissable(int x, int y)
{
	if(_Tableau[x][y]==B00)
	{
		return true;
	}else{
		return false;
	}
}

void Map::setInfranchissable(int x, int y)
{
	_Tableau[x][y]=B01;
}

void Map::setFranchissable(int x, int y)
{
	_Tableau[x][y]=B00;
}

void Map::setTemporairementInfranchissable(int x, int y)
{
	_Tableau[x][y]=_Tableau[x][y] | B10;
}
void Map::setRestoreEtat(int x, int y)
{
	_Tableau[x][y]=_Tableau[x][y] & B01;
}
