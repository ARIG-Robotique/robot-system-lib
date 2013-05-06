/*
 * Collection.cpp
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#include "Collection.h"
#include <stdlib.h>

/*Declaration des fonctions de la classe Collection*/

Collection::Collection(){

	_PremierObject = NULL;
	_DernierObject = NULL;
	_CourantObject = NULL;
	_NbObjects = 0;
	_IndexCourant = -1;

}

bool Collection::isFinListe(){
	if(_IndexCourant>=_NbObjects)
	{
		return true;
	}else{
		return false;
	}
}

bool Collection::isDebutListe(){
	if(_IndexCourant<=0)
	{
		return true;
	}else{
		return false;
	}
}

void Collection::suivant()
{
	if(isFinListe() == false && _CourantObject != NULL )
	{
		_CourantObject = _CourantObject->getObjectSuivant();
		_IndexCourant++;
	}
}

void Collection::precedent()
{
	if(isDebutListe() ==false && _CourantObject != NULL)
	{
		_CourantObject = _CourantObject->getObjectPrecedant();
		_IndexCourant--;
	}
}

Object * Collection::recupererObject()
{

	return _CourantObject;

}

bool Collection::ajouterNoeud(Noeud * n)
{

	Object* new_Object;
	new_Object = (Object*)malloc(sizeof(Object));

	if(new_Object !=NULL)
	{
		new_Object->setNoeud(n);
		new_Object->setIndex(_NbObjects);

		_CourantObject = new_Object;
		_IndexCourant = _NbObjects;
		_NbObjects++;

		if(_PremierObject==NULL)
		{
			new_Object->setObjectSuivant(NULL);
			new_Object->setObjectPrecedant(NULL);
			_PremierObject = new_Object;
			_DernierObject = new_Object;
		}else{
			new_Object->setObjectPrecedant(_DernierObject);
			new_Object->setObjectSuivant(NULL);
			_DernierObject = new_Object;
		}
		return true;
	}else{
		return false;
	}
}

bool Collection::noeudExiste(Point p)
{
	Object * sauvegardeObjectCourant;
	bool trouver;
	sauvegardeObjectCourant = _CourantObject; // On sauvergarde l'objectCourant

	trouver = false;

	if(_CourantObject->getNoeud()->getPoint().equal(p)==true)
	{
			trouver=true;
	}else
	{
		_CourantObject = _PremierObject;
		trouver = false;

		while (isFinListe()==false)
		{
			if(_CourantObject->getNoeud()->getPoint().equal(p) == true)
			{
				trouver = true;
				break;
			}
			suivant();
		}
	}

	if(trouver == false)
	{
		_CourantObject = sauvegardeObjectCourant;
	}

	return trouver;
}

Noeud * Collection::rechercherNoeud(Point p)
{

	if(this->rechercherNoeud(p)==true){
		return _CourantObject->getNoeud();
	}else
	{
		return NULL;
	}

}

Noeud * Collection::getNoeudCourant()
{
	if(_NbObjects>0)
	{
		return _CourantObject->getNoeud();
	}else{
		return NULL;
	}
}

Point Collection::getPointCourant()
{

	if(_NbObjects>0)
	{
		return _CourantObject->getNoeud()->getPoint();
	}else{
		return NULL;
	}

}

bool Collection::remplacerNoeud(Noeud *n){

	if(_NbObjects>0)
	{

		_CourantObject->setNoeud(n);
		return true;
	}else{
		return false;
	}

}

bool Collection::supprimerNoeud(Noeud *n)
{
	// TODO : A implementer



	return true;
}

bool Collection::supprimerNoeudCourant()
{

	if(_NbObjects>0)
	{

		Object* tObject_Precedant;
		Object* tObject_Suivant;

		tObject_Precedant= _CourantObject->getObjectPrecedant();
		tObject_Suivant= _CourantObject->getObjectSuivant();

		tObject_Precedant->setObjectSuivant(tObject_Suivant);
		tObject_Suivant->setObjectPrecedant(tObject_Precedant);

		free(_CourantObject);
		_NbObjects --;

		if(_NbObjects>0){
			_CourantObject = tObject_Suivant;
		}

		return true;
	}else
	{
		return false;
	}




}

int Collection::getNbObjects(){
	return _NbObjects;
}

/*void Collection::toString()
{
	/*#ifdef DEBUG_ASTAR
	Serial.print("Nb objects  : ");
	Serial.print(_NbObjects);
	Serial.print(" indexCourant : ");
	Serial.println(_IndexCourant);
	#endif

}*/

