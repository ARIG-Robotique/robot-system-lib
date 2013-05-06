/*
 * ObjectListe.h
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "../Noeud.h"
#include <Arduino.h>

class Object
{
	private :
		Noeud * _Noeud;
		Object *_ObjectSuivant;
		Object *_ObjectPrecedant;
		int _Index;

	public :
		Object();
		Object( Object *suivant, Object *precedant, Noeud * n, int index);

		Object* getObjectSuivant();
		Object* getObjectPrecedant();
		void setObjectSuivant(Object * suivant);
		void setObjectPrecedant(Object * precedant);

		Noeud * getNoeud();
		void setNoeud(Noeud * n);

		void setIndex(int i);
		int getIndex();
};


#endif /* OBJECT_H_ */
