/*
 * ObjectListe.cpp
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#include "Object.h"
#include <stdlib.h>


Object::Object()
{
	_Index = -1;

}

Object::Object(Object * suivant, Object * precedant, Noeud *n, int index)
{

	_Index = index;
	_ObjectSuivant = suivant;
	_ObjectPrecedant = precedant;
	_Noeud = n;

}

Object * Object::getObjectSuivant(){
	return _ObjectSuivant;
}

Object * Object::getObjectPrecedant(){
	return _ObjectPrecedant;
}

void Object::setObjectSuivant(Object * suivant){
	_ObjectSuivant = suivant;
}

void Object::setObjectPrecedant(Object * precedant){
	_ObjectPrecedant = precedant;
}

void Object::setNoeud(Noeud * n){
	_Noeud = n;
}

Noeud * Object::getNoeud(){
	return _Noeud;
}

void Object::setIndex(int index){
	_Index = index;
}

int Object::getIndex(){
	return _Index;
}


