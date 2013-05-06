/*
 * Collection.h
 *
 *  Created on: 1 févr. 2013
 *      Author: daoh
 */

#ifndef COLLECTION_H_
#define COLLECTION_H_

#include "Object.h"
#include <Arduino.h>

class Collection
{
	private :
		Object * _PremierObject;
		Object * _DernierObject;
		Object * _CourantObject;
		int _NbObjects;
		int _IndexCourant;
		//ObjectListe * rechercherObject(Noeud *n);
		Object * recupererObject();

	public :
		Collection();
		bool isFinListe();
		bool isDebutListe();
		void suivant();
		void precedent();
		Noeud * rechercherNoeud(Point p);
		bool noeudExiste (Point p);
		bool remplacerNoeud(Noeud * n);
		//ObjectListe* rechercherObject(ObjectListe n);
		//boolean ObjectExist(ObjectListe n);
		bool ajouterNoeud(Noeud * n);
		Noeud * getNoeudCourant();
		Point getPointCourant();
		bool supprimerNoeud(Noeud *n);
		bool supprimerNoeudCourant();
		//void toString();
		int getNbObjects();
};


#endif /* COLLECTION_H_ */
